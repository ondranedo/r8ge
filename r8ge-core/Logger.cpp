
#include "Logger.h"

#include <iostream>

#include "fileio/FileIO.h"

namespace r8ge {
    namespace global {
        Logger* logger = nullptr;
    }

    Logger::Logger() : m_queue{},m_running(true){
        m_thread = std::thread(&Logger::logLoop, this);
    }
    Logger::~Logger() {
        m_running = false;
        m_thread.join();
        emptyLogQueue();
    }

    void Logger::log(Priority p, const std::string& raw) {
        m_mutex.lock();
        m_queue.emplace(raw, p);
        m_mutex.unlock();
    }

    void Logger::emptyLogQueue() {
        m_mutex.lock();
        while(!m_queue.empty()) {
            Log& l = m_queue.front();
            global::fileIO->writeStdout(format(l)+"\n");

            m_queue.pop();
        }
        m_mutex.unlock();
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

    void Logger::logLoop() {
        while(m_running) {
            emptyLogQueue();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void mainLog(Logger::Priority p, const std::string &parser,
                 const std::initializer_list<utility::StringFormat::ValidType> &t) {
        if(global::logger)
            global::logger->log(p, utility::StringFormat(parser, t).to_string());
        else {
            global::fileIO->writeStderr("Error: Main logger not initialized\n");
            global::fileIO->writeStdout(utility::StringFormat(parser, t).to_string() + "\n");
        }
    }

    Logger::Log::Log(const std::string &raw, Logger::Priority p) : raw_data(raw), priority(p), times(TimeStamp()){}
}