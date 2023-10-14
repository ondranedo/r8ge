
#include "Logger.h"


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
            Console::log(format(l)+"\n");
            m_queue.pop();
        }
        m_mutex.unlock();
    }

    std::string Logger::format(const Log& log) {
        std::string str;
        str+= "[" + log.times.to_string("%X:%^{ms}") + "] "; // TODO: Log formats
        str+= "[";
        str+= priorityToString(log.priority);
        str+= "] - " + log.raw_data;
        return str;
    }

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
        }
        return "unknown";
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

    Logger::Log::Log(const std::string &raw, Logger::Priority p) : raw_data(raw), priority(p), times(TimeStamp()){}
}