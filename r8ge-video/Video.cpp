#include "Video.h"

#include <r8ge/r8ge.h>
#include <iostream>

#include "renderingService/buffers/IndexBuffer.h"
#include "renderingService/buffers/VertexBuffer.h"
#include "types/Vertex.h"
#include "renderingService/openGL/GLTexture.h"
#include "renderingService/programManager/Program.h"
#include "renderer/Camera.h"
#include "renderingService/openGL/GLFrameBuffer.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace r8ge {

    ImGuiIO io;
    bool show_demo_window = true;
    bool show_another_window = false;
    float deltaTime = 0.0f;    // time between current frame and last frame
    float lastFrame = 0.0f;
    r8ge::video::Camera cam(0.0f,0.0f,3.0f,0.0f,1.0f,-1.0f);

    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    std::shared_ptr<video::GUIService> Video::s_guiService = nullptr;

    bool Video::s_isReady = false;

    Video::Video() : m_title("R8GE-video Engine") {
        // TODO: Config file, rendering API
        s_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);

        s_windowingService = video::WindowingService::create();
        s_guiService = video::GUIService::create();

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
        s_windowingService->setEventCallbacks();
        s_windowingService->setGLContext();
        s_renderingService->init();
        s_guiService->init(*s_windowingService);


        s_windowingService->setVsync(1);
        R8GE_LOG("R8GE-Video initialized");
    }

    void Video::run() {

        R8GE_LOG("Video starting to run main loop");
        s_renderingService->setClearColor(ColorRGBA{0, 0, 30, 0});
        video::Program basic_program(0, "shaders/glm.glsl");
        s_renderingService->compileProgram(basic_program);

        // TODO: Fetch raw data from Renderer
        video::IndexBuffer ib({0, 1, 3, 1, 2, 3});
        std::vector<VertexTexture3D> vertices = {
                {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
                {0.5f,  -0.5f, -0.5f, 1.0f, 0.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},

                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},
                {0.5f,  -0.5f, 0.5f,  1.0f, 0.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
                {-0.5f, 0.5f,  0.5f,  0.0f, 1.0f},
                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},

                {-0.5f, 0.5f,  0.5f,  1.0f, 0.0f},
                {-0.5f, 0.5f,  -0.5f, 1.0f, 1.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},
                {-0.5f, 0.5f,  0.5f,  1.0f, 0.0f},

                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {0.5f,  -0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f,  -0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f,  -0.5f, 0.5f,  0.0f, 0.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f,  -0.5f, -0.5f, 1.0f, 1.0f},
                {0.5f,  -0.5f, 0.5f,  1.0f, 0.0f},
                {0.5f,  -0.5f, 0.5f,  1.0f, 0.0f},
                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},

                {-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
                {-0.5f, 0.5f,  0.5f,  0.0f, 0.0f},
                {-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f}
        };


        video::VertexBuffer vb(vertices, vertices[0].getLayout());

        s_renderingService->setVertexBuffer(vb);
        s_renderingService->setIndexBuffer(ib);

        s_renderingService->preRender();
        video::Texture2D tex2D1("textures/morce.jpg", true);
        video::Texture2D tex2D2("textures/spsetrans.png", true);
        video::GLTexture glTex1(tex2D1);
        video::GLTexture glTex2(tex2D2);

        s_renderingService->setProgram(basic_program);
        s_renderingService->setUniformInt(basic_program, "texture1", 0);
        s_renderingService->setUniformInt(basic_program, "texture2", 1);


        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) s_windowingService->getWidth() /
                                                                     (float) s_windowingService->getHeight(), 0.1f, 100.0f);
        s_renderingService->setUniformMat4(basic_program, "projection", projection);

        r8ge::video::GLFrameBuffer frameBuffer(s_windowingService->getWidth(),s_windowingService->getHeight());
        glTex1.bindTexture(0);
        glTex2.bindTexture(1);
        while (Ar8ge::isRunning()) {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            cam.changeCameraPosition(deltaTime,0,0);

            // Begin GUI frame
            s_guiService->beginFrame();

            // Bind the framebuffer and enable depth testing
            frameBuffer.bind();
            glEnable(GL_DEPTH_TEST);

            // Clear the framebuffer
            s_renderingService->clear();

            // Set model and view matrices
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, currentFrame, glm::vec3(0.5f, 1.0f, 0.0f));

            s_renderingService->setProgram(basic_program);
            s_renderingService->setUniformMat4(basic_program, "model", model);
            s_renderingService->setUniformMat4(basic_program, "view", cam.getViewMatrix());

            s_renderingService->render();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            frameBuffer.unbind();
            glDisable(GL_DEPTH_TEST);

            s_guiService->render(frameBuffer);

            s_guiService->endFrame(*s_windowingService);

            // Swap buffers and handle events
            s_windowingService->swapBuffersOfMainWindow();
            s_windowingService->poolEvents();
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

    std::shared_ptr<video::GUIService> Video::getGUIService() {
        return s_guiService;
    }
}