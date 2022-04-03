/******************************************************************************
* File:             log_linter.hpp
*
* Author:           BxNiom  
* Created:          04/03/22 
*                   Linter for message format
*****************************************************************************/

#ifndef __BXLOG_LOG_LINTER_HPP__
#define __BXLOG_LOG_LINTER_HPP__

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "log_level.hpp"
#include "log_info.hpp"

namespace bxniom { namespace log {
    
   class Linter {
       public:
            class FormatItem {
                public:
                    virtual ~FormatItem() { }
                    virtual std::string parse(LogInfo& info) { return ""; }
            };

           class StringItem : public virtual FormatItem {
                private:
                    std::string _value;
                public:
                    StringItem(std::string value) : _value(value) {}
                    std::string parse(LogInfo& info) override { return _value; }
            };

            class DateTimeItem : public virtual FormatItem {
                private:
                    std::string _fmt;
                public:
                    DateTimeItem(std::string fmt) : _fmt(fmt) {}
                    std::string parse(LogInfo& info) override {
                        char buf[32];
                        std::tm* ptm = std::localtime(&info.timestamp);
                        std::strftime(buf, 32, _fmt.c_str(), ptm);
                        return std::string(buf);
                    }
            };

           class LevelItem : public virtual FormatItem {
               private:
                   bool _upper = false;
                   bool _lower = false;
               public:
                   LevelItem(bool upper, bool lower) : _upper(upper), _lower(lower) {}
                   std::string parse(LogInfo& info) override {
                       std::string res = bxniom::log::to_string(info.level);
                       if (_upper) {
                           transform(res.begin(), res.end(), res.begin(), ::toupper);
                       } else if(_lower) {
                           transform(res.begin(), res.end(), res.begin(), ::tolower);
                       }

                       return res;
                   }
           };

#define __PROPERTY_ITEM( n, p )                                 \
   class n: public virtual Linter::FormatItem {                 \
       public:                                                  \
            n() { }                                             \
            std::string parse(LogInfo& info) override {    \
                return info.p;                                  \
            }                                                   \
   };                                                           \

            __PROPERTY_ITEM(FilenameItem, file)
            __PROPERTY_ITEM(LineItem, line)
            __PROPERTY_ITEM(FunctionItem, fn)
            __PROPERTY_ITEM(ThreadItem, threadId)
            __PROPERTY_ITEM(MessageItem, msg)

       private:
            std::list<FormatItem*> _items;
            Linter() { }
            void decode(std::string format, int pos);
            std::string readUntil(std::string s, int& pos, char until);
        public:
            static Linter create(std::string format);
            std::string parse(LogInfo& info);       
   }; 


}}

#endif /* end of include guard: __BXLOG_LOG_LINTER_HPP__ */
