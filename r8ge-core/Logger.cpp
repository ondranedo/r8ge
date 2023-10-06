
#include "Logger.h"

#include <iostream>

namespace r8ge {
    std::mutex mainLogger_mutex;
    Logger* mainLogger;

    Logger::Logger() : m_queue{}{}
    Logger::~Logger() {
        emptyLogQueue();
    }

    void Logger::log(Priority p, const std::string& raw) {
        mainLogger_mutex.lock();
        m_queue.emplace(raw, p);
        mainLogger_mutex.unlock();

        if(p == Priority::FATAL)
            emptyLogQueue();
    }

    void Logger::emptyLogQueue() {
        mainLogger_mutex.lock();
        while(!m_queue.empty()) {
            Log& l = m_queue.front();
            // TODO: Platform output
            std::cout << format(l) << std::endl;

            m_queue.pop();
        }
        mainLogger_mutex.unlock();
    }

    std::string Logger::format(const Log& log) {
        std::string str;
        str+= "[" + log.times.to_string("%X:%^{ms}") + "] "; // TODO: Log formats
        str+= "[";
        switch (log.priority) {
            case Priority::FATAL: str+= "fatal"; break;
            case Priority::DEBUG: str+= "debug"; break;
            case Priority::ERROR: str+= "error"; break;
            case Priority::TRACE: str+= "trace"; break;
            case Priority::WARNI: str+= "warni"; break;
        }
        str+= "] - " + log.raw_data;
        return str;
    }

    Logger::Log::Log(const std::string &raw, Logger::Priority p) : raw_data(raw), priority(p) {}

    void mainLog(Logger::Priority p, const std::string &parser,
                 const std::initializer_list<utility::StringFormat::ValidType> &t) {
        if(mainLogger)
            mainLogger->log(p, utility::StringFormat(parser, t).to_string());

        // TODO: Some error output or smth
    }
}