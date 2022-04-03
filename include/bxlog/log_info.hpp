/******************************************************************************
* File:             log.hpp
*
* Author:           BxNiom
* Created:          04/02/22
*****************************************************************************/

#ifndef __BXLOG_LOG_INFO_HPP
#define __BXLOG_LOG_INFO_HPP

#include "log_level.hpp"
#include <string>
#include <ctime>

namespace bxniom { namespace log {

    struct LogInfo {
        std::string msg;
        LogLevel level;
        std::time_t timestamp;
        std::string file;
        std::string fn;
        std::string line;
        std::string threadId;
    };

}}

#endif /* end of include guard: __BXLOG_LOG_INFO_HPP */
