#include "Video.h"

#include <r8ge/r8ge.h>
#include <X11/Xlib.h>

#include "renderingService/buffers/IndexBuffer.h"
#include "renderingService/buffers/VertexBuffer.h"
#include "renderingService/Vertex.h"

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
        s_windowingService->init();

        s_windowingService->createMainWindow(800, 600, m_title);

        s_renderingService->init();

        R8GE_LOG_INFOR("R8GE-Video initialized");
    }

    void Video::run() {
        R8GE_LOG("Video starting to run main loop");

        while(Ar8ge::isRunning()) {
            s_windowingService->poolEvents();

            // TODO: Config file, key bindings
            if(m_input.isKeyPressed({Code::ESCAPE, Code::MBUTTON_LEFT})) {
                EventPayload p;
                p.setEvent(std::make_shared<EngineKill>());
                Ar8ge::getEventQueue()(p);
            }

            s_renderingService->setClearColor({0x54,0x54,0x54});
            s_renderingService->clear();

            //r8ge::Rectangle r1(0.5, 0.25);

            // TODO: Fetch raw data from Renderer
            //s_renderingService->render(r1.getIndices(), r1.getVertices());
            video::IndexBuffer ib({0, 1, 2048, 2, 3, 0});
            std::vector<Vertex> vertices = {
                     {-0.5f, -0.5f}, {0.0f, 0.0f},
                     {0.5f, -0.5f},  {1.0f, 0.0f},
                     {0.5f, 0.5f},   {1.0f, 1.0f},
                     {-0.5f, 0.5f},  {0.0f, 1.0f}
            };

            video::VertexBuffer vb(vertices, video::VertexBufferLayout({video::VertexBufferLayout::Entry::POS_XY}));

            auto vec = ib.getData();

            auto data = vb.getData<Vertex>();

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