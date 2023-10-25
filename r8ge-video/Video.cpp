#include "Video.h"

#include <cmath>

#include <r8ge/r8ge.h>
#include <X11/Xlib.h>

#include "renderingService/buffers/IndexBuffer.h"
#include "renderingService/buffers/VertexBuffer.h"
#include "types/Vertex.h"

#include "renderingService/programManager/Program.h"
#include "renderingService/programManager/ProgramData.h"

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

        R8GE_LOG_INFOR("R8GE-Video initialized");
    }

    void Video::run() {
        R8GE_LOG("Video starting to run main loop");

        // TODO: Fetch raw data from Renderer
        video::IndexBuffer ib({0,3,2,0,1,2});
        std::vector<Vertex> vertices = {
                {-1.f,-1.f},
                {-1.f, 1.f},
                { 1.f, 1.f},
                { 1.f,-1.f}
        };

        video::VertexBuffer vb(vertices, vertices[0].getLayout());

        s_renderingService->setIndexBuffer(ib);
        s_renderingService->setVertexBuffer(vb);

        s_renderingService->setClearColor({0x54,0x54,0x54});

        video::Program basic_program(0, "shaders/mandelbrot.glsl");

        s_renderingService->compileProgram(basic_program);
        s_renderingService->setProgram(basic_program);

        float dir_x = 1, dir_y = 1;
        float zoom = 0.5;
        float hash[3] = {6513.4564,4522.1232,1123.9414};

        while(Ar8ge::isRunning()) {
            s_windowingService->poolEvents();

            s_renderingService->clear();

            {
                float scale = 0.01;

                if(Input::isKeyPressed(Key::W)) dir_y -= scale;
                if(Input::isKeyPressed(Key::A)) dir_x += scale;
                if(Input::isKeyPressed(Key::S)) dir_y += scale;
                if(Input::isKeyPressed(Key::D)) dir_x -= scale;

                if(Input::isKeyPressed(Key::Q)) zoom += 0.001;
                if(Input::isKeyPressed(Key::E)) zoom -= 0.001;

                if(Input::isKeyPressed(Key::N1)) hash[0] += 0.01;
                if(Input::isKeyPressed(Key::N2)) hash[1] += 0.01;
                if(Input::isKeyPressed(Key::N3)) hash[1] += 0.01;

                // SEND DATA To Uniform

                union {
                    float resolution[2];
                    uint8_t raw[sizeof(float) * 2];
                } uresolution = {
                        static_cast<float>(s_windowingService->getHeightOfMainWindow()),
                        static_cast<float>(s_windowingService->getWidthOfMainWindow())};
                video::ProgramData resolution("resolution", {uresolution.raw,uresolution.raw+sizeof(float) * 2}, video::ProgramData::Type::VEC2);
                s_renderingService->sendProgramData(basic_program, resolution);

                // Move dire
                union {
                    float dir[2];
                    uint8_t raw[sizeof(float) * 2];
                } umovedir = {dir_x, dir_y};
                video::ProgramData movedir("move_dir", {umovedir.raw,umovedir.raw+sizeof(float) * 2}, video::ProgramData::Type::VEC2);
                s_renderingService->sendProgramData(basic_program, movedir);

                // Move dire
                union {
                    float zoom;
                    uint8_t raw[sizeof(float)];
                } uzoom = {zoom};
                video::ProgramData zoomo("zoom", {uzoom.raw,uzoom.raw+sizeof(float)}, video::ProgramData::Type::VEC1);
                s_renderingService->sendProgramData(basic_program, zoomo);

                // Hash
                // Move dire
                union {
                    float hash[3];
                    uint8_t raw[sizeof(float)*3];
                } uhash;
                uhash.hash[0] = hash[0];
                uhash.hash[1] = hash[1];
                uhash.hash[2] = hash[2];
                video::ProgramData hasho("hash", {uhash.raw,uhash.raw+sizeof(float)*3}, video::ProgramData::Type::VEC3);
                //s_renderingService->sendProgramData(basic_program, hasho);
            }

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