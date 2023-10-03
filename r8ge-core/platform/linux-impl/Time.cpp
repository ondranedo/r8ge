#include "../Time.h"

#include <time.h>
#include <chrono>

namespace r8ge {

    Time::Time() {
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime(&rawtime);
        m_year = timeinfo->tm_year+1900;
        m_month = timeinfo->tm_mon+1;
        m_day = timeinfo->tm_mday;
        m_hour = timeinfo->tm_hour;
        m_minute = timeinfo->tm_min+1;
        m_second = timeinfo->tm_sec;

        auto res = std::chrono::high_resolution_clock::now();
        m_microseconds = res.time_since_epoch().count();

    }

    std::string Time::to_string(const std::string& format) {
        std::string s = "";
        s+=std::to_string(m_year) + ":";
        s+=std::to_string(m_month) + ":";
        s+=std::to_string(m_day) + " ";
        s+=std::to_string(m_hour)+ ":";
        s+=std::to_string(m_minute) + ":";
        s+=std::to_string(m_second);

        return s;
    }

    std::size_t Time::getExact(Time::_point timePoint) {
        switch (timePoint) {
            case YEAR: return m_year;
            case MONTH:return m_month;
            case DAY: return m_day;
            case HOUR: return m_hour;
            case MINUTE:return m_minute;
            case SECOND: return m_second;
        }
        return 0;
    }
}