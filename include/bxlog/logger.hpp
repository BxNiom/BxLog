/******************************************************************************
* File:             logger.hpp
*
* Author:           BxNiom  
* Created:          04/03/22 
*                   Basic logger
*****************************************************************************/

#ifndef __BXLOG_LOGGER_HPP__
#define __BXLOG_LOGGER_HPP__

#include "log_level.hpp"
#include <string>
#include <iostream>

namespace bxniom { namespace log {

    class Logger {
        public:
            virtual ~Logger() {}
            virtual void write(const LogLevel lvl, const std::string& msg) = 0;
    };

    class ConsoleLogger : public virtual Logger {
        public:
            void write(const LogLevel lvl, const std::string &msg) override {
                if (lvl == LogLevel::Error) {
                    std::cerr << msg << "\n";
                    std::cerr.flush();
                } else {
                    std::cout << msg << "\n";
                    std::cout.flush();
                }
            }
    };

}}

#endif /* end of include guard: __BXLOG_LOGGER_HPP__ */
