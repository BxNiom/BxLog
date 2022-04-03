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


#define BX_LOG(level) bxniom::log::LogWrapper(bxniom::log::LogLevel::level, __FILE__, __FUNCTION__, __LINE__, std::this_thread::get_id())

#define BX_LOG_IF(level, condition) if (condition) BX_LOG(level)
#define BX_LOG_LEVEL(level) bxniom::log::Log::getInstance()->maxLevel(bxniom::log::LogLevel::level)

#endif /* end of include guard: __BXLOG_HPP */