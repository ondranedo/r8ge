#ifndef R8GE_TIME_H
#define R8GE_TIME_H

#include <string>

namespace r8ge {
    class Time {
    public:
        enum _point {
            YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, MILLISECOND, MICROSECOND, NANOSECONDS
          //%Y   %M     %D   %h    %m      %s       %q           %u
        };


        Time();

        [[nodiscard]] std::string to_string(const std::string& format = "%Y:%M:%D %h:%m:%s");
        [[nodiscard]] std::size_t getExact(_point timePoint);
        [[nodiscard]] std::size_t getDur(_point timePoint);
        Time& operator-(const Time&);

    private:

        // Used for measuring time
        std::size_t m_nanoseconds;
    };


}

#endif//!R8GE_TIME_H
