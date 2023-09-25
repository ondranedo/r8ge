
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
            m_queue.pop();

            // TODO: Platform output
            std::cout << format(l) << std::endl;
        }
        mainLogger_mutex.unlock();
    }

    std::string Logger::format(const Log& log) {
        std::string str;
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
}