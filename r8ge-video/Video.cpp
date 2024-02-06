#include "Video.h"

#include <r8ge/r8ge.h>
#include <iostream>

#include "renderingService/openGL/GLTexture.h"
#include "renderingService/programManager/Program.h"
#include "renderer/Camera.h"
#include "renderingService/openGL/GLFrameBuffer.h"
#include "GLFW/glfw3.h"

#include "renderer/Model.h"
#include "imgui_internal.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <ImGuizmo.h>

namespace r8ge {
    float deltaTime = 0.0f;    // time between current frame and last frame
    float lastFrame = 0.0f;
    r8ge::video::Camera cam(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, -1.0f);

    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    std::shared_ptr<video::GUIService> Video::s_guiService = nullptr;
    r8ge::video::GLFrameBuffer frameBuffer;


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
        s_windowingService->setVsync(true);
        R8GE_LOG("R8GE-Video initialized");
    }

    void Video::run() {
        R8GE_LOG("Video starting to run main loop");
        video::Program basic_program(0, "shaders/model.glsl");
        video::Program test_program(1, "shaders/test.glsl");
        s_renderingService->compileProgram(basic_program);
        r8ge::video::Model modelBackpack("backpack/backpack.obj");
        r8ge::video::Texture2D tex1("test",false);
        s_windowingService->setFrameBuffer(frameBuffer);
        frameBuffer.setBuffer(s_windowingService->getWidth(), s_windowingService->getHeight());;
        glEnable(GL_DEPTH_TEST);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                static_cast<float>(s_windowingService->getWidth()) /
                                                static_cast<float>(s_windowingService->getHeight()), 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,
                               glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model,
                           glm::vec3(1.0f, 1.0f, 1.0f));
        while (Ar8ge::isRunning()) {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            cam.changeCameraPosition(deltaTime, 0, 0);

            s_guiService->beginFrame();

            frameBuffer.bind();

            s_renderingService->setClearColor(ColorRGBA{0, 0, 30, 1.0});
            s_renderingService->clear();


            s_renderingService->setProgram(basic_program);

            s_renderingService->setUniformMat4(basic_program, "projection", projection);
            glm::mat4 view = cam.getViewMatrix();
            s_renderingService->setUniformMat4(basic_program, "view", view);


            s_renderingService->setUniformMat4(basic_program, "model", model);

            modelBackpack.render(basic_program);


            frameBuffer.unbind();

            ImGui::Begin("Viewport",nullptr,ImGuiWindowFlags_NoMove);
            {

                ImGui::Image(
                        (ImTextureID) frameBuffer.getFrameTexture(),
                        ImGui::GetContentRegionAvail(),
                        ImVec2(0, 1),
                        ImVec2(1, 0)
                );
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();
                ImGuizmo::SetRect(ImGui::GetWindowPos().x,ImGui::GetWindowPos().y,ImGui::GetWindowHeight(),ImGui::GetWindowHeight());
                ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(model));
            }

            ImGui::End();


            s_guiService->render(frameBuffer);

            s_guiService->endFrame(*s_windowingService);

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
