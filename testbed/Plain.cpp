#include <r8ge/r8ge.h>
#include <r8ge/video.h>
#include <memory>


r8ge::ColorRGBA color(0x000000);

class GameLayer : public r8ge::Layer {

public:

    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

        int f;
/*
        //r8ge::Video::getWindowingService()->setContextOfMainWindow();
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);
        //r8ge::Video::getWindowingService()->poolEvents();

        //r8ge::Video::getRenderingService()->
        */
    }

    void update() override {
        color.r = 0x00;
        color.b = 0x30;
        color.g = 0x00;
    }

    void event(const std::shared_ptr<r8ge::Event> &event) override {
        r8ge::Video::getRenderingService()->setClearColor(color);
    }

    void render() override {
/*

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("Hello, world!");
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        */

    }
};

class PlainApp : public r8ge::GameInstance {

public:
    PlainApp() : r8ge::GameInstance("testbedGame") {
    }

    ~PlainApp() override = default;

    void onInit() override {
        R8GE_LOG("`{}` game initialization", getGameName());
        layerSwitcher().add<GameLayer>();
    }

    void onUpdate() override {

    }

    void onExit() override {
        R8GE_LOG("`{}` game exiting", getGameName());
        /*
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
         */
    }
};

R8GE_ADD_INSTANCE(PlainApp);