
#include "Logger.h"
#include <ranges>
#include <cstring>

namespace r8ge {
    namespace global {
        Logger* logger = nullptr;
    }

    Logger::Logger(const std::string& format) : m_queue{},m_running(true), m_format(format+"%c")
    {
        m_thread = std::thread(&Logger::logLoop, this);
    }

    Logger::~Logger() {
        m_running = false;
        m_thread.join();
        emptyLogQueue();
    }

    void Logger::log(Priority p, const std::string& raw) {
        m_mutex.lock();
        m_queue.emplace(raw, p, m_format);
        m_mutex.unlock();
    }

    void Logger::emptyLogQueue() {
        m_mutex.lock();
        while(!m_queue.empty()) {
            Log& raw_l = m_queue.front();
            FormatAndLog(raw_l);
            Console::log("\n");
            m_queue.pop();
        }
        m_mutex.unlock();
    }

    void Logger::FormatAndLog(const Log& log) {
        std::string str;
        size_t countlock = 0;
        bool default_size = true;
        bool uppercase = false;
        bool log_style = false;

        for(auto [i, c] : log.format | std::views::enumerate)
        {
            if(c == '%')
            {
                std::string fromSpec = formatSpecifier(i+1, log, countlock, default_size, uppercase, log_style);

                if(default_size)
                    str+=fromSpec;
                else
                {
                    uppercase ?
                        std::transform(fromSpec.begin(), fromSpec.end(), fromSpec.begin(), ::toupper):
                        std::transform(fromSpec.begin(), fromSpec.end(), fromSpec.begin(), ::tolower);
                    str+=fromSpec;
                }
            }
            else
                if(!(countlock>0?countlock--:countlock)) str+=c;


            if(log_style)
                Console::set(makeStyle(m_default_style[static_cast<int>(log.priority)]));
            else
                Console::setDefault();

            Console::log(str);
            str="";
        }

        Console::log(str);
    }

    std::string Logger::formatSpecifier(const size_t index, const Logger::Log &log, size_t &countlock, bool& default_size, bool& uppercase, bool& log_style) {
        switch (log.format[index]) {
            case '%': countlock+=1; return "%";
            case 'H': countlock+=1; return log.times.to_string("%H");
            case 'M': countlock+=1; return log.times.to_string("%M");
            case 'S': countlock+=1; return log.times.to_string("%S");
            case 'm': countlock+=1; return log.times.to_string("%^{ms}");
            case 'u': countlock+=1; return log.times.to_string("%^{us}");
            case 'n': countlock+=1; return log.times.to_string("%^{ns}");
            case 'X': countlock+=1; return log.times.to_string("%X");
            case '^': countlock+=1; return log.times.to_string("%^{ms}:%^{us}:%^{ns}");
            case 'l': countlock+=1; return log.raw_data;
            case 'L': countlock+=1; return priorityToString(log.priority);
            case 'o': // TODO: originated from
            case 't': countlock+=1; return "unknown"; // TODO: thread id
            case 'U': countlock+=1; default_size=false; uppercase=true; return "";
            case 'D': countlock+=1; default_size=false; uppercase=false; return "";
            case '<': countlock+=1; default_size=true; uppercase=false; return "";
            // ConsoleParams
            case 'C':{ countlock+=1;
                log_style = true;
            return "";}
            case 'c': countlock+=1;
                log_style = false;
            return "";
            /*case '<':
                countlock+=formatSpecifierM(index+1, log);
                log_next = true;
                return "";
            case 'r': countlock+=1;
                param = makeStyle(m_current_style[static_cast<int>(log.priority)]);
                log_next = true;
            return "";
            case 'R': countlock+=1;
                param.useDefaultBackgroundColor = true;
                param.useDefaultForegroundColor = true;
                param.blink = false;
                param.italic = false;
                param.bold = false;
                param.underline = Console::NOT_UNDERLINED;
                log_next = true;
            return "";*/
        }
        return "";
    }

    /*size_t Logger::formatSpecifierM(const size_t index, const Logger::Log &log) {
        char sw = log.format[index];
        std::string data = log.format.substr(index+1, log.format.find('>')-index-1);
        auto hexToColor = [&](const std::string& hex) -> Console::Color{
            uint8_t r = std::stoi(hex.substr(0, 2), nullptr, 16);
            uint8_t g = std::stoi(hex.substr(2, 2), nullptr, 16);
            uint8_t b = std::stoi(hex.substr(4, 2), nullptr, 16);
            return {r,g,b};
        };

        switch (sw) {
            case 'f':
                param.foregroundColor=hexToColor(data.substr(1, 6));
            break;
            case 'b':
                param.backgroundColor=hexToColor(data.substr(1, 6));
            break;
            case 'r': {
                Console::ConsoleParam s = makeStyle(m_current_style[static_cast<int>(log.priority)]);
                if(data == "f") param.foregroundColor = s.foregroundColor;
                if(data == "b") param.backgroundColor = s.backgroundColor;
                break;
            }
            case 'q': {
                if(data == "1") param.bold = true;
                if(data == "0") param.bold = false;
                break;
            }
            case 'i': {
                if(data == "1") param.italic = true;
                if(data == "0") param.italic = false;
                break;
            }
            case 'u': {
                if(data == "1") param.underline = Console::NOT_UNDERLINED;
                if(data == "0") param.underline = Console::NOT_UNDERLINED;
                break;
            }
            case 'F': {
                if(data == "1") param.blink = true;
                if(data == "0") param.blink = false;
                break;
            }
        }

        return 3 + data.size();
    }*/

    void Logger::logLoop() {
        while(m_running) {
            emptyLogQueue();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    std::string Logger::priorityToString(Logger::Priority p) {
        switch (p) {
            case Priority::FATAL: return "fatal";
            case Priority::DEBUG: return "debug";
            case Priority::ERROR: return "error";
            case Priority::TRACE: return "trace";
            case Priority::WARNI: return "warni";
            case Priority::INFOR: return "infor";
        }
        return "unknown";
    }

    Console::ConsoleParam Logger::makeStyle(const Style &style) {
        Console::ConsoleParam param;
        param.useDefaultBackgroundColor = style.db;
        param.useDefaultForegroundColor = style.df;
        param.foregroundColor = style.f;
        param.backgroundColor = style.b;
        param.bold = style.bold;
        param.italic = style.italic;
        param.blink = style.blink;
        param.underline = Console::NOT_UNDERLINED;

        return param;
    }

    void Logger::setFormat(const std::string &format) {
        m_format = format+"%c";
    }

    void mainLog(Logger::Priority p, const std::string &parser,
                 const std::initializer_list<utility::StringFormat::ValidType> &t) {
        if(global::logger)
            global::logger->log(p, utility::StringFormat(parser, t).to_string());
        else {
            Console::log("Error: Main logger not initialized\n");
            Console::log(utility::StringFormat(parser, t).to_string() + "\n");
        }
    }

    Logger::Log::Log(const std::string &raw, Logger::Priority p, const std::string& f) :
    raw_data(raw), priority(p), times(TimeStamp()), format(f){}
}