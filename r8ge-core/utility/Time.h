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

        // Used for measuring time
        std::size_t m_microseconds;
    };


}

#endif//!R8GE_TIME_H
