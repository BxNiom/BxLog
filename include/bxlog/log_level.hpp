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
        None = 0,
        Error = 1,
        Warning = 2,
        Info = 3,
        Debug = 4,
        Verbose = 5
    };

    static std::string to_string(LogLevel l) {
        switch(l)
        {
            case LogLevel::None: return "None";
            case LogLevel::Error: return "Error";
            case LogLevel::Warning: return "Warning";
            case LogLevel::Info: return "Info";
            case LogLevel::Debug: return "Debug";
            case LogLevel::Verbose: return "Verbose";
        }

        return "Unknown";
    }

    static std::ostream& operator<<(std::ostream& os, LogLevel l) {
        switch(l)
        {
            case LogLevel::None: os << "LogLevel::None"; return os;
            case LogLevel::Error: os << "LogLevel::Error"; return os;
            case LogLevel::Warning: os << "LogLevel::Warning"; return os;
            case LogLevel::Info: os << "LogLevel::Info"; return os;
            case LogLevel::Debug: os << "LogLevel::Debug"; return os;
            case LogLevel::Verbose: os << "LogLevel::Verbose"; return os;
        }

        return os << "LogLevel::Unknown";
    }
}}

#endif /* end of include guard: __BXLOG_LEVEL_HPP__ */
