#include "TimeStamp.h"

#include <time.h>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "../Core.h"

#define NS_TO_SEC 1000000000

namespace r8ge {

    TimeStamp::TimeStamp() : m_nanoseconds(std::chrono::system_clock::now().time_since_epoch().count()),m_subtracted(false){}

    TimeStamp &TimeStamp::operator-(const TimeStamp & a) {
        R8GE_ASSERT(this->m_nanoseconds > a.m_nanoseconds, "Can't compare two time() objects; right object as larger");
        this->m_nanoseconds -= a.m_nanoseconds;
        this->m_subtracted = true;
        return *this;
    }

    std::size_t TimeStamp::sinceEpoch(TimeStamp::_point timePoint) const {
        R8GE_ASSERT(!m_subtracted, "Can't convert TimeStamp() to string after it has been compared with other TimeStamp() objects");

        auto epoch = static_cast<std::time_t>(m_nanoseconds/NS_TO_SEC);
        std::tm* local = std::localtime(&epoch);

        switch (timePoint) {
            case YEAR:   return local->tm_year+1900;
            case MONTH:  return local->tm_mon+1;
            case DAY:    return local->tm_mday;
            case HOUR:   return local->tm_hour;
            case MINUTE: return local->tm_min;
            case SECOND: return local->tm_sec;
            case MILLISECOND: return (m_nanoseconds/1000000)%1000;
            case MICROSECOND: return (m_nanoseconds/1000)%1000;
            case NANOSECONDS: return m_nanoseconds%1000;
        }
        return 0;
    }

    std::size_t TimeStamp::count(TimeStamp::_point timePoint) const {
        size_t seconds = m_nanoseconds/(1000000000);

        switch (timePoint) {
            case YEAR:   return seconds/31536000;
            case MONTH:  return seconds/2592000;
            case DAY:    return seconds/86400;
            case HOUR:   return seconds/3600;
            case MINUTE: return seconds/60;
            case SECOND: return seconds;
            case MILLISECOND: return m_nanoseconds/(1000000);
            case MICROSECOND: return m_nanoseconds/(1000);
            case NANOSECONDS: return m_nanoseconds;
        }

        return 0;
    }

    std::string strtftime(const std::string& format, std::tm* localtime)
    {
        char buff[80];
        std::strftime(buff, 80, format.c_str(), localtime);
        return buff;
    }

    std::string TimeStamp::customFormat(const std::string &format) const {
        std::string out = format;

        struct listi {
            std::string s;
            TimeStamp::_point p;
        };

        listi list[3] = {
                {"%^{ms}", MILLISECOND},
                {"%^{us}", MICROSECOND},
                {"%^{ns}", NANOSECONDS}};

        size_t check = 0;

        for(auto & i : list) {
            do {
                if ((check = out.find(i.s)) != std::string::npos) {
                    out.erase(check, i.s.length());
                    out.insert(check, std::to_string(sinceEpoch(i.p)));
                }
            } while (check != std::string::npos);
        }

        return out;
    }

    std::string TimeStamp::to_string(const std::string &format) const {
        R8GE_ASSERT(!m_subtracted, "Can't convert TimeStamp() to string after it has been compared with other TimeStamp() objects");

        auto epoch = static_cast<std::time_t>(m_nanoseconds/NS_TO_SEC);
        std::tm* local = std::localtime(&epoch);

        std::string strt = strtftime(format, local);

        return customFormat(strt);
    }
}