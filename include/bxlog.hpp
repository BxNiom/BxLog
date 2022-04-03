/******************************************************************************
* File:             bxlog.hpp
*
* Author:           BxNiom
* Created:          04/02/22
* Description:      Global header for BxLog
*****************************************************************************/

#ifndef __BXLOG_HPP
#define __BXLOG_HPP

#include "bxlog/log.hpp"
#include "bxlog/log_info.hpp"
#include "bxlog/log_level.hpp"
#include "bxlog/log_linter.hpp"
#include "bxlog/log_wrapper.hpp"
#include "bxlog/logger.hpp"

#include <thread>

#define error 1
#define warn 2
#define info 3
#define debug 4
#define verbose 5

#define BX_LOG(level) bxniom::log::LogWrapper(level, __FILE__, __FUNCTION__, __LINE__, std::this_thread::get_id())

#define BX_LOG_IF(level, condition) if (condition) BX_LOG(level)

#endif /* end of include guard: __BXLOG_HPP */