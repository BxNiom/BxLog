/******************************************************************************
* File:             log.hpp
*
* Author:           BxNiom  
* Created:          04/02/22 
*                   Basic log header with types and functions
*****************************************************************************/

#ifndef __BXLOG_LOG_HPP__
#define __BXLOG_LOG_HPP__

#include "log_level.hpp"
#include "logger.hpp"
#include "log_linter.hpp"

#include <ctime>
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <thread>
#include <mutex>

namespace bxniom { namespace log {

    class Linter;

    class Log {
        friend class Linter;
        private:

        private:
            static Log* _singletone;

            bool _running = false;
            std::thread* _loop;
            std::deque<LogInfo> _logQueue;
            std::list<Logger*> _logger;
            std::string _msgFormat = "[%d %t] %lv.upper | %ti | %fi(%ln): %m";
            Linter _linter;
            std::mutex _mtx;

            Log();
            
            void run();
            void write();

            static void close() { close(0); }

            static void close(int s) {
                Log* l = getInstance();
                if (l->_running)
                    l->_running = false;

                if (l->_loop->joinable())
                    l->_loop->joinable();

                while(!l->_logQueue.empty()) {
                    l->write();
                }
            }
        public:
            static Log* getInstance() {
                if (!Log::_singletone)
                    Log::_singletone = new Log();

                return Log::_singletone;
            }
            
            void add(Logger* logger);

            void write(LogLevel lvl, std::string msg, 
                    std::string file, std::string fn, std::string ln,
                    std::thread::id threadid);

            std::string format() const { return _msgFormat; }
            void format(std::string format);
    };
}}

#endif /* end of include guard: __BXLOG_LOG_HPP__ */
