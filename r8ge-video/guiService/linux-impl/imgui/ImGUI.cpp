//
// Created by karnatour on 15.1.24.
//


#include "ImGUI.h"
#include "../../../../r8ge-core/Logger.h"

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>


namespace r8ge {
    namespace video {
        std::shared_ptr<GUIService> GUIService::create() {
            return std::make_shared<ImGUI>();
        }

        ImGUI::~ImGUI() = default;

        void ImGUI::init(WindowingService &service) {
            if (service.getWindow() == nullptr) {
                R8GE_LOG_ERROR("Provided window is null, init WindowingService first");
            }

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void) io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            float fontSize = 18.0f;
            io.FontDefault = io.Fonts->AddFontFromFileTTF("fonts/Raleway/static/Raleway-Regular.ttf", fontSize);

            ImGui::StyleColorsDark();

            ImGuiStyle &style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            ImGui_ImplGlfw_InitForOpenGL(service.getWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 460");
        }

        void ImGUI::exit() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void ImGUI::beginFrame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void ImGUI::render() {
            ImGui::Render();
        }

        void ImGUI::endFrame(WindowingService &service) {
            ImGuiIO &io = ImGui::GetIO();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow *backup_current_context = service.getWindow();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }


        void ImGUI::showDemoWindow() {
            bool demo;
            ImGui::ShowDemoWindow(&demo);
        }


    } // r8ge
} // video