#include "Time.h"

#include <time.h>
#include <chrono>
#include <sstream>
#include "../Core.h"

#define NS_TO_SEC 1000000000

namespace r8ge {

    Time::Time() : m_nanoseconds(std::chrono::system_clock::now().time_since_epoch().count()){}

    std::string Time::to_string(const std::string& format) {
        std::stringstream ss;

        return ss.str();
    }

    std::size_t Time::getExact(Time::_point timePoint) {
        std::time_t epoch = static_cast<std::time_t>(m_nanoseconds/NS_TO_SEC);
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

    Time &Time::operator-(const Time & a) {
        R8GE_ASSERT(this->m_nanoseconds > a.m_nanoseconds, "Can't compare two time() objects; right object as larger");
        this->m_nanoseconds -= a.m_nanoseconds;
        return *this;
    }

    std::size_t Time::getDur(Time::_point timePoint) {
        //TODO: implement

        return 0;
    }
}