/******************************************************************************
* File:             log_linter.cpp
*
* Author:           BxNiom  
* Created:          04/03/22 
*****************************************************************************/

#include "log_linter.hpp"
#include <sys/select.h>

using namespace bxniom::log;

Linter Linter::create(std::string fmt) {
    Linter linter;
    linter.decode(fmt, 0);

    return std::move(linter);
}

void Linter::decode(std::string fmt, int pos) {
    std::string dateFmt, timeFmt, mod;

    while (pos < fmt.length()) {
        if (fmt[pos] != '%') {
            _items.push_back(new StringItem(readUntil(fmt, pos, '%')));
            continue;
        } else {
            pos++;
            switch (fmt[pos]) {
                case 'd':
                    if (fmt[pos + 1] == '(') {
                        dateFmt = readUntil(fmt, ++pos, ')');
                    } else {
                        dateFmt = "%Y-%m-%d";
                    }
                    _items.push_back(new DateTimeItem(dateFmt));
                    pos++;
                    continue;
                case 't':
                    if (fmt[pos + 1] == 'i') {
                        _items.push_back(new ThreadItem());
                        pos += 2;
                        continue;
                    }

                    if (fmt[pos + 1] == '(') {
                        timeFmt = readUntil(fmt, ++pos, ')');
                    } else {
                        timeFmt = "%H:%M:%S";
                    }
                    _items.push_back(new DateTimeItem(timeFmt));
                    pos++;
                    continue;
                case 'f':
                    pos++;
                    if (fmt[pos] == 'n') {
                        _items.push_back(new FunctionItem());
                        pos++;
                        continue;
                    } else if (fmt[pos] == 'i') {
                        _items.push_back(new FilenameItem());
                        pos++;
                        continue;
                    }
                    break;
                case 'l':
                    pos++;
                    if (fmt[pos] == 'v') { // Level
                        if (fmt[pos + 1] == '.') {
                            mod = readUntil(fmt, ++pos, 'r') + "r";

                            if (mod == ".upper" || mod == ".lower") {
                                _items.push_back(new LevelItem(mod == ".upper", mod == ".lower"));
                                pos++;
                                continue;
                            }
                        } else {
                            _items.push_back(new LevelItem(false, false));
                            pos++;
                            continue;
                        }
                    } else if (fmt[pos] == 'n') { // Line
                        _items.push_back(new LineItem());
                        pos++;
                        continue;
                    }
                    break;
                case 'm':
                    _items.push_back(new MessageItem());
                    pos++;
                    continue;
            }

            std::string msg = "Log format mismatch at position " + std::to_string(pos) + ". Format: " + fmt + "\n";
            std::cerr << msg;
            throw std::runtime_error(msg);
        }
    }
}

std::string Linter::readUntil(std::string s, int& pos, char until) {
    std::string res = "";
    while (pos < s.length() && s[pos] != until) {
        res += s[pos++];
    }

    return res;
}

std::string Linter::parse(LogInfo& info) {
    std::string res = "";
    for(auto it: _items) {
        res += it->parse(info);
    }

    return res;
}

