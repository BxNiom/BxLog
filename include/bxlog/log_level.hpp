/******************************************************************************
* File:             level.hpp
*
* Author:           BxNiom  
* Created:          04/02/22 
*                   Log levels
*****************************************************************************/

#ifndef __BXLOG_LEVEL_HPP__
#define __BXLOG_LEVEL_HPP__

#include <ostream>
#include <string>

namespace bxniom { namespace log {

    enum class LogLevel {
        none = 0,
        error = 1,
        warning = 2,
        info = 3,
        debug = 4,
        verbose = 5
    };

    static std::string to_string(LogLevel l) {
        switch(l)
        {
            case LogLevel::none: return "None";
            case LogLevel::error: return "Error";
            case LogLevel::warning: return "Warning";
            case LogLevel::info: return "Info";
            case LogLevel::debug: return "Debug";
            case LogLevel::verbose: return "Verbose";
        }

        return "Unknown";
    }

    static std::ostream& operator<<(std::ostream& os, LogLevel l) {
        switch(l)
        {
            case LogLevel::none: os << "LogLevel::None"; return os;
            case LogLevel::error: os << "LogLevel::Error"; return os;
            case LogLevel::warning: os << "LogLevel::Warning"; return os;
            case LogLevel::info: os << "LogLevel::Info"; return os;
            case LogLevel::debug: os << "LogLevel::Debug"; return os;
            case LogLevel::verbose: os << "LogLevel::Verbose"; return os;
        }

        return os << "LogLevel::Unknown";
    }
}}

#endif /* end of include guard: __BXLOG_LEVEL_HPP__ */
