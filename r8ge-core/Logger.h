#ifndef R8GE_LOGGER_H
#define R8GE_LOGGER_H

#include <string>
#include <chrono>
#include <queue>
#include <mutex>
#include <thread>

#include "utility/StringFormat.h"
#include "utility/TimeStamp.h"
#include "platform/Console.h"

namespace r8ge {
    class Logger;
    namespace global {
        extern Logger* logger;
    }


    // Logger class, used to log messages to a file (or stdout for now)
    class Logger {
    public:
        Logger(const std::string& format = "[%X %m:%u] %l"); // TODO: specify log file (default STDOUT)
        ~Logger();

        enum class Priority {
            TRACE, INFOR, DEBUG, ERROR, WARNI, FATAL
        };


        std::string priorityToString(Priority p);
    private:
        struct Log {
            TimeStamp times;
            std::string raw_data;
            Priority priority;
            std::string format;

            Log(const std::string& raw, Priority p, const std::string& format);
        };

    public:
        // Sends a log to the queue, to be processed later by the logger
        void log(Priority p, const std::string& str);

        //      %% - outputs `%`
        //
        //      %H - Hours (0;24]
        //      %M - Minutes (0;60]
        //      %S - Seconds (0;60]
        //      %m - Milliseconds (0;1000]
        //      %u - Microseconds (0;1000]
        //      %n - Nanoseconds (0;1000]
        //      %X - %H:%M:%S
        //      %^ - %m:%u:%n
        //
        //      %l - log message
        //      %L - log level ("trace", "debug", "error", "warni", "fatal")
        //      %o - originated from ("engine", "client", "server", "unknown")
        //      %t - thread id
        //
        //      %U - All next characters will be uppercase
        //      %D - All next characters will be lowercase
        //
        //      Output styles:
        //      %C - Set to specified log level color
        //      %c - Reset colors
        //      %r - Reset all styles, colors to default for log level
        //      %R - Reset all styles, colors to default
        //      %<f#RRGGBB> - Set foreground color to 0xRRGGBB
        //      %<b#RRGGBB> - Set background color to 0xRRGGBB
        //      %<rb> - Reset foreground color
        //      %<rf> - Reset background color
        //      %<q1> - Set bold onn
        //      %<q0> - Set bold off
        //      %<i1> - Set italic on
        //      %<i0> - Set italic off
        //      %<u1> - Set underline on
        //      %<u0> - Set underline off
        //      %<F1> - Set blink on
        //      %<F0> - Set blink off
        //
        //      For output styles:
        //         Styled    - S
        //         Default   - D
        //
        //         <------\ <-------\ <--------\ <------\
        //             S  |     D   |     S    |     S  |
        //        "[data] %C [data] %c [data] %C" ... "%C%c"
        //
        //        - Without de-specifier, the default style is used
        void setFormat(const std::string& format);
    private:
        // Empties the log queue, and writes all logs to the log file (stdout for now)
        void emptyLogQueue();

        [[nodiscard]] std::string formatSpecifier(Console::ConsoleParam& param,const size_t index, const Log& log, size_t& countlock, bool& default_size, bool& uppercase, bool& log_next);
        size_t formatSpecifierM(Console::ConsoleParam& param,const size_t index, const Log& log);
        void FormatAndLog(Console::ConsoleParam& param, const Log& log);

        // Main loop of the logger, called by the constructor
        void logLoop();


    private:
        struct Style{
            Priority p;
            Console::Color f, b;
            bool df, db;
            bool bold;
            bool italic;
            bool blink;
        } m_current_style[6] = {
                // LEVEL          FOREGROUND    BACKGROUND   DE_F   DE_B  BOLD   ITALIC BLINK
                {Priority::TRACE,{ 73, 73, 73},{255,255,255},false, true ,false, true , false},
                {Priority::INFOR,{116,165, 73},{255,255,255},false, true ,false, false, false},
                {Priority::DEBUG,{73 ,116,165},{255,255,255},false, true ,false, false, false},
                {Priority::ERROR,{165, 73,116},{255,255,255},false, true ,true , false, true},
                {Priority::WARNI,{165,122, 73},{255,255,255},false, true ,false, false, true},
                {Priority::FATAL,{215,197,229},{122, 73,165},false, false,true , false, false}
        };
        Console::ConsoleParam makeStyle(const Style& style);

    private:

        std::string m_format;
        std::queue<Log> m_queue;
        std::thread m_thread;
        std::mutex m_mutex;
        bool m_running;
    };


    // Main Logger function, takes StringFormat::ValidType as arguments (see utility/StringFormat.h),
    // and call to the mainLogger (which is a global object)
    void mainLog(Logger::Priority p, const std::string& parser,
                 const std::initializer_list<utility::StringFormat::ValidType>& t);
}

#define R8GE_LOG_TRACE(str, ...) r8ge::mainLog(r8ge::Logger::Priority::TRACE, str,{__VA_ARGS__})
#define R8GE_LOG_INFOR(str, ...) r8ge::mainLog(r8ge::Logger::Priority::INFOR, str,{__VA_ARGS__})
#define R8GE_LOG_DEBUG(str, ...) r8ge::mainLog(r8ge::Logger::Priority::DEBUG, str,{__VA_ARGS__})
#define R8GE_LOG_WARNI(str, ...) r8ge::mainLog(r8ge::Logger::Priority::WARNI, str,{__VA_ARGS__})
#define R8GE_LOG_ERROR(str, ...) r8ge::mainLog(r8ge::Logger::Priority::ERROR, str,{__VA_ARGS__})
#define R8GE_LOG_FATAL(str, ...) r8ge::mainLog(r8ge::Logger::Priority::FATAL, str,{__VA_ARGS__})

#define R8GE_LOG(...) R8GE_LOG_TRACE(__VA_ARGS__)

#endif//!R8GE_LOGGER_H
