#include <r8ge/r8ge.h>

class GameLayer : public r8ge::Layer {
public:
    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

    }

    void update() const override {

    }

    void event(const std::shared_ptr<r8ge::Event> &event) const override {
        R8GE_LOG_DEBUG("{} received {} event", getName(), event->to_string());
    }

    void render() const override {

    }
};

class MenuLayer : public r8ge::Layer {
public:
    ~MenuLayer() override = default;

    MenuLayer() : r8ge::Layer("menuLayer") {

    }

    void update() const override {

    }

    void event(const std::shared_ptr<r8ge::Event> &event) const override {
        R8GE_LOG_DEBUG("{} received {} event", getName(), event->to_string());
    }

    void render() const override {

    }
};

class TestbedGame : public r8ge::GameInstance {
public:
    TestbedGame() : r8ge::GameInstance("testbedGame") {}
    ~TestbedGame() override = default;

    void onInit()  override {
        R8GE_LOG("`{}` game initialization", getGameName());

        layerSwitcher().add<GameLayer>();

        // Menu layer will be rendered last, so it will be on top of the game layer
        // But events will be sent to the game layer first
        layerSwitcher().add<MenuLayer>();
    }

    void directEvent(const std::shared_ptr<r8ge::Event> &event) override {
        // There is going to be a list of events that are handled directly by the game instance
        // f.e. window resize, window close, BUTTON_ESC pressed, etc.
    }

    void onUpdate() override {

    }

    void onExit()  override {
        R8GE_LOG("`{}` game exiting", getGameName());
    }
};

R8GE_ADD_GAMEINSTANCE(TestbedGame);

