#include "Video.h"

#include "EntrytPoint.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace global {
        std::unique_ptr<Video> video;
    }

    Video::Video() : m_isRunning(false) , m_windowingService(video::WindowingService::create()) {}
    Video::~Video() {}

    void Video::init() {
        m_windowingService->init();

        video::WindowingService::setActiveService(m_windowingService);

        R8GE_LOG_INFOR("R8GE-Video initialized");
    }

    void Video::exit() {
        video::WindowingService::releaseService();

        m_windowingService->release();

        R8GE_LOG_INFOR("R8GE-Video released");
    }

    void Video::run() {
        while(global::ar8geRunning) {

        }
        R8GE_LOG_DEBUG("Video running");
    }
}