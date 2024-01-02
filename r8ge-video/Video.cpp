#include "Video.h"

#include <r8ge/r8ge.h>
#include <X11/Xlib.h>
#include <iostream>

#include "renderingService/buffers/IndexBuffer.h"
#include "renderingService/buffers/VertexBuffer.h"
#include "types/Vertex.h"

#include "renderingService/programManager/Program.h"

namespace r8ge {
    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    bool Video::s_isReady = false;

    Video::Video() : m_title("R8GE-video Engine") {
        // TODO: Config file, rendering API
        s_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);

        s_windowingService = video::WindowingService::create();

        s_windowingService->setKeyPressedCallback(Input::getKeyActionCallback());
        s_windowingService->setMousePressedCallback(Input::getMouseActionCallback());
    }

    Video::~Video() {
        s_windowingService = nullptr;
        s_renderingService = nullptr;
    }

    void Video::init() {
        s_windowingService->init();

        s_windowingService->createMainWindow(800, 600, m_title);

        s_renderingService->init();

        R8GE_LOG("R8GE-Video initialized");
    }

    void Video::run() {
        R8GE_LOG("Video starting to run main loop");

        // TODO: Fetch raw data from Renderer
        video::IndexBuffer ib({0, 1, 2});
        std::vector<VertexColor> vertices = {
                {0.5f, -0.5f, ColorRGB(255, 0, 0)},
                {-0.5f,  -0.5f, ColorRGB(0, 255, 0)},
                {0.0f,  0.5f,  ColorRGB(0, 0, 255)},
        };

        std::cout<< sizeof(VertexColor);

        video::VertexBuffer vb(vertices, vertices[0].getLayout());

        s_renderingService->setIndexBuffer(ib);
        s_renderingService->setVertexBuffer(vb);

        s_renderingService->setClearColor({0x54, 0x54, 0x54,0x00});

        video::Program basic_program(0, "shaders/basic.glsl");

        s_renderingService->compileProgram(basic_program);
        s_renderingService->setProgram(basic_program);

        while (Ar8ge::isRunning()) {
            s_windowingService->poolEvents();

            s_renderingService->clear();

            s_renderingService->render();

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