#ifndef R8GE_TIMESTAMP_H
#define R8GE_TIMESTAMP_H

#include <string>

namespace r8ge {
    class TimeStamp {
    public:
        enum _point {
            YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, MILLISECOND, MICROSECOND, NANOSECONDS
          //%Y   %M     %D   %h    %m      %s       %q           %u
        };
        TimeStamp();

        TimeStamp& operator-(const TimeStamp&);
        [[nodiscard]] std::size_t sinceEpoch(TimeStamp::_point timePoint) const;
        [[nodiscard]] std::size_t count(TimeStamp::_point timePoint) const;
        [[nodiscard]] std::string to_string(const std::string& format = "%Y:%m:%d %H:%M:%S") const;
    private:
        // Used for measuring time
        std::size_t m_nanoseconds; // Since epoch
        bool m_subtracted;
    };


}

#endif//!R8GE_TIMESTAMP_H
