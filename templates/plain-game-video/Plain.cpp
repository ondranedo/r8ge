#include <r8ge/r8ge.h>
#include <r8ge/video.h>

class GameLayer : public r8ge::Layer {
public:
    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {}

    void update() const override {}

    void event(const std::shared_ptr<r8ge::Event> &event) const override {
        r8ge::event::Dispatcher dispatcher(event);
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
        r8ge::event::Dispatcher dispatcher(event);
    }

    void render() const override {

    }
};

class PlainApplication : public r8ge::GameInstance {
public:
    PlainApplication() : r8ge::GameInstance("PlainApplication") {}
    ~PlainApplication() override = default;

    void onInit()  override {
        R8GE_LOG("`{}` game initialization", getGameName());

        layerSwitcher().add<GameLayer>();

        // Menu layer will be rendered last, so it will be on top of the game layer
        // But events will be sent to the game layer first
        layerSwitcher().add<MenuLayer>();
    }

    void directEvent(const std::shared_ptr<r8ge::Event> &event) override {
        r8ge::event::Dispatcher dispatcher(event);

        dispatcher.dispatch<r8ge::KeyPressed>([](const std::shared_ptr<r8ge::KeyPressed>& event) -> bool {
            R8GE_LOG_DEBUG("Key pressed: {} [Sx{};Ax{};Cx{};Sux{}]",
                           r8ge::to_string(event->stroke.iocode),
                           static_cast<bool>(event->stroke.shift),
                           static_cast<bool>(event->stroke.alt),
                           static_cast<bool>(event->stroke.ctrl),
                           static_cast<bool>(event->stroke.super)
            );
            return true;
        });
    }

    void onUpdate() override {

    }

    void onExit()  override {
        R8GE_LOG("`{}` game exiting", getGameName());
    }
};

R8GE_ADD_GAMEINSTANCE(PlainApplication);
