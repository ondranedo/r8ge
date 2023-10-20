#include "Video.h"

#include "EntrytPoint.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    bool Video::s_isReady = false;

    Video::Video() : m_title("R8GE-video Engine") {
        s_windowingService = video::WindowingService::create();
    }
    Video::~Video() {}

    void Video::init() {
        s_windowingService->init();

        s_windowingService->createWindow(800, 600, m_title);

        R8GE_LOG_INFOR("R8GE-Video initialized");
    }

    void Video::run() {
        R8GE_LOG("Video starting to run main loop");

        s_windowingService->showWindow(m_title);

        while(Ar8ge::isRunning()) {
            s_windowingService->updateWindows();
        }
    }

    void Video::exit() {
        s_windowingService->destroyWindow(m_title);

        s_windowingService->release();

        R8GE_LOG_INFOR("R8GE-Video released");
    }

    std::shared_ptr<video::WindowingService> Video::getWindowingService() {
        return s_windowingService;
    }
}