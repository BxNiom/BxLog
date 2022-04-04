/******************************************************************************
* File:             log.cpp
*
* Author:           BxNiom  
* Created:          04/03/22 
*****************************************************************************/

#include "log.hpp"

#include <exception>
#include <unistd.h>
#include <chrono>
#include <sstream>
#include <csignal>

using namespace bxniom::log;
using namespace std::chrono_literals;

Log* Log::_singletone = 0;

Log::Log() : _linter(Linter::create(_msgFormat)) {
    signal(SIGABRT, Log::close);
    signal(SIGTERM, Log::close);
    atexit(Log::close);

    add(new ConsoleLogger());

    run();
}

void Log::run() {
    _running = true;
    _loop = new std::thread([&] {
        while (_running) {
            write();
            std::this_thread::sleep_for(1ms);
        }
    });
    _loop->detach();
}

void Log::write() {
    if (!_logQueue.empty()) {
        _mtx.lock();
        auto msg = _linter.parse(_logQueue.front());

        for (Logger* it: _logger) {
            it->write(_logQueue.front().level, msg);
        }

        _logQueue.pop_front();
        _mtx.unlock();
    }
}

void Log::add(Logger* logger) {
    std::lock_guard<std::mutex> lock(_mtx);
    _logger.push_back(logger);
}

void Log::format(std::string format) {
    std::lock_guard<std::mutex> lock(_mtx);
    _msgFormat = format;
    _linter = Linter::create(format);
}

void Log::write(LogLevel lvl, std::string msg,
                std::string file, std::string fn, std::string ln,
                std::thread::id threadid) {

    if (lvl > _level) return;

    LogInfo info;
    info.level = lvl;
    info.msg = msg;

    int l;
    if ((l = file.find_last_of('/')) < file.length()) {
        info.file = file.substr(l + 1);
    } else {
        info.file = file;
    }

    info.fn = fn;
    info.line = ln;
    info.timestamp = std::time(NULL);

    std::stringstream oss;
    oss << "0x" << std::hex << threadid;
    info.threadId = oss.str();

    std::lock_guard<std::mutex> lock(_mtx);
    _logQueue.push_back(info);
}
