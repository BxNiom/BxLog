/******************************************************************************
* File:             bxlog.hpp
*
* Author:           BxNiom
* Created:          04/02/22
*****************************************************************************/

#ifndef __BXLOG_LOG_WRAPPER_HPP
#define __BXLOG_LOG_WRAPPER_HPP

#include "log.hpp"
#include "log_level.hpp"

#include <sstream>
#include <string>

namespace bxniom { namespace log {

    class LogWrapper {
        private:
            LogLevel _lvl;
            std::string _file;
            std::string _func;
            std::string _line;
            std::thread::id _threadId;
            std::stringstream _ss;
        public:
            LogWrapper(LogLevel lvl, const char* file, const char* func, int line, std::thread::id threadId)
                    : _lvl(lvl), _file(file), _func(func), _line(std::to_string(line)), _threadId(threadId) {
            }

            ~LogWrapper() {
                Log::getInstance()->write(_lvl,
                                          _ss.str(),
                                          _file,
                                          _func,
                                          _line,
                                          _threadId);
            }

            template<class T>
            LogWrapper& operator<<(T value) {
                _ss << value;
                return *this;
            }
    };

}}

#endif //__BXLOG_LOG_WRAPPER_HPP
