#ifndef R8GE_TIMESTAMP_H
#define R8GE_TIMESTAMP_H

#include <string>

namespace r8ge {
    // TimeStamp class, used for measuring time, and converting time to string.
    // May be used for measuring time between two points.
    class TimeStamp {
    public:
        enum _point {
            YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, MILLISECOND, MICROSECOND, NANOSECONDS
          //%Y   %M     %D   %h    %m      %s       %q           %u
        };
        TimeStamp();

        // Converts localtime (time since epoch ISO 8601) to `TimeStamp::_point`,
        // if we use this for differing between times, an error is thrown.
        //    TimeStamp t1; // Time is: 2023-10-06 15:15:16 ....
        //    // ...
        //
        //    t1.sinceEpoch(TimeStamp::SECOND); -> 16
        //    t1.sinceEpoch(TimeStamp::HOUR); -> 15
        //    t1.sinceEpoch(TimeStamp::YEAR); -> 2023
        //    t1.sinceEpoch(TimeStamp::DAY); -> 6
        [[nodiscard]] std::size_t sinceEpoch(TimeStamp::_point timePoint) const;

        // Counts how many `TimeStamp::_point` have passed since POSIX time
        // ,not counting leap seconds (in ISO 8601: 1970-01-01T00:00:00Z).
        // If we use `TimeStamp` in calculation f.e:
        //    TimeStamp t1;
        //    // ...
        //    TimeStamp t2;
        //    (t2-t1).count(TimeStamp::SECOND);
        // It outputs how many seconds have passed since `t1` creation to `t2` creation
        [[nodiscard]] std::size_t count(TimeStamp::_point timePoint) const;

        // Uses https://strftime.org/ format, with addition to custom time formats for formating
        // milliseconds - %^{ms}
        // microseconds - %^{us}
        // nanoseconds  - %^{ns}
        [[nodiscard]] std::string to_string(std::string_view format = "%Y:%m:%d %H:%M:%S") const;

    public:
        TimeStamp& operator-(const TimeStamp&);

    private:
        [[nodiscard]] std::string customFormat(std::string_view format) const;

    private:
        std::size_t m_nanoseconds; // Since epoch
        bool m_subtracted;
    };


}

#endif//!R8GE_TIMESTAMP_H
