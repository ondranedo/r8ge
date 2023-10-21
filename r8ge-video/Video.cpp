#include "Video.h"

#include "EntrytPoint.h"

#include <r8ge/r8ge.h>
#include <GL/glew.h>

namespace r8ge {
    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    bool Video::s_isReady = false;

    Video::Video() : m_title("R8GE-video Engine") {
        // TODO: Config file, rendering API
        s_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);


        s_windowingService = video::WindowingService::create();
        s_windowingService->setKeyPressedCallback(m_input.getKeyActionCallback());
        s_windowingService->setMousePressedCallback(m_input.getMouseActionCallback());
    }
    Video::~Video() {
        s_windowingService = nullptr;
        s_renderingService = nullptr;
    }

    void Video::init() {
        s_renderingService->init();
        s_windowingService->init();

        s_windowingService->createMainWindow(800, 600, m_title);

        R8GE_LOG_INFOR("R8GE-Video initialized");
    }

    void Video::run() {
        R8GE_LOG("Video starting to run main loop");

        while(Ar8ge::isRunning()) {
            s_windowingService->poolEvents();

            // TODO: Config file, key bindings
            if(m_input.isKeyPressed({IOCode::ESCAPE, IOCode::MBUTTON_LEFT})) {
                EventPayload p;
                p.setEvent(std::make_shared<EngineKill>());
                Ar8ge::getEventQueue()(p);
            }

            glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            s_windowingService->swapBuffersOfMainWindow();
        }
    }

    void Video::exit() {
        s_windowingService->destroyMainWindow();

        s_windowingService->exit();


        s_renderingService->exit();
        R8GE_LOG_INFOR("R8GE-Video released");
    }

    std::shared_ptr<video::WindowingService> Video::getWindowingService() {
        return s_windowingService;
    }

    std::shared_ptr<video::RenderingService> Video::getRenderingService() {
        return s_renderingService;
    }
}