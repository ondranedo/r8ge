#include "Time.h"

#include <time.h>
#include <chrono>
#include <sstream>

namespace r8ge {

    Time::Time() :m_microseconds(std::chrono::high_resolution_clock::now().time_since_epoch().count()){}

    std::string Time::to_string(const std::string& format) {
        std::stringstream ss;

        return ss.str();
    }

    std::size_t Time::getExact(Time::_point timePoint) {
        switch (timePoint) {
            //case YEAR: return m_microseconds;
            //case MONTH:return m_month;
            //case DAY: return m_day;
            //case HOUR: return m_hour;
            //case MINUTE:return m_minute;
            //case SECOND: return (m_microseconds/1000000);
        }
        return 0;
    }
}