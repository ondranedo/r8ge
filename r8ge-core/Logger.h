#ifndef R8GE_LOGGER_H
#define R8GE_LOGGER_H

#include <string>
#include <chrono>
#include <queue>
#include <mutex>

#include "utility/StringFormat.h"
#include "utility/TimeStamp.h"

namespace r8ge {
    class Logger;
    extern Logger* mainLogger;

    class Logger {
    public:
        Logger(); // TODO: specify log file (default STDOUT), and format
        ~Logger();

        enum class Priority {
            TRACE, DEBUG, ERROR, WARNI, FATAL
        };

    private:
        struct Log {
            TimeStamp times;
            std::string raw_data;
            Priority priority;

            Log(const std::string& raw, Priority p);
        };

    public:
        // Sends a log to the queue, to be processed later by the logger
        void log(Priority p, const std::string& str);

        // Empties the log queue, and writes all logs to the log file (stdout for now)
        void emptyLogQueue();

    private:
        std::string format(const Log& log);
        std::queue<Log> m_queue;
    };


    // Main Logger function, takes StringFormat::ValidType as arguments (see utility/StringFormat.h),
    // and call to the mainLogger (which is a global object)
    void mainLog(Logger::Priority p, const std::string& parser,
                 const std::initializer_list<utility::StringFormat::ValidType>& t);
}

#define R8GE_LOG_TRACE(str, ...) r8ge::mainLog(r8ge::Logger::Priority::TRACE, str,{__VA_ARGS__})
#define R8GE_LOG_DEBUG(str, ...) r8ge::mainLog(r8ge::Logger::Priority::DEBUG, str,{__VA_ARGS__})
#define R8GE_LOG_WARNI(str, ...) r8ge::mainLog(r8ge::Logger::Priority::WARNI, str,{__VA_ARGS__})
#define R8GE_LOG_ERROR(str, ...) r8ge::mainLog(r8ge::Logger::Priority::ERROR, str,{__VA_ARGS__})
#define R8GE_LOG_FATAL(str, ...) r8ge::mainLog(r8ge::Logger::Priority::FATAL, str,{__VA_ARGS__})

#define R8GE_LOG(...) R8GE_LOG_TRACE(__VA_ARGS__)

#endif//!R8GE_LOGGER_H
