#ifndef R8GE_TIME_H
#define R8GE_TIME_H

#include <string>

namespace r8ge {
    class Time {
    public:
        enum _point {
            YEAR, MONTH, DAY, HOUR, MINUTE, SECOND
          //%Y   %M     %D   %h    %m      %s
        };


        Time();

        [[nodiscard]] std::string to_string(const std::string& format = "%Y:%M:%D %h:%m:%s");
        [[nodiscard]] std::size_t getExact(_point timePoint);

    private:
        std::size_t m_year:12;
        std::size_t m_month:4;
        std::size_t m_day:5;
        std::size_t m_hour:5;
        std::size_t m_minute:6;
        std::size_t m_second:6;

        // USed for measuring time
        std::size_t m_microseconds;
    };


}

#endif//!R8GE_TIME_H
