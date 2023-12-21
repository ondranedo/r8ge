#include <r8ge/r8ge.h>
#include <r8ge/video.h>

class GameLayer : public r8ge::Layer {
public:
    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {}

    void update() const  {}

    void event(const std::shared_ptr<r8ge::Event> &event) const  {
        r8ge::event::Dispatcher dispatcher(event);
    }

    void render() const  {

    }
};

class MenuLayer : public r8ge::Layer {
public:
    ~MenuLayer() override = default;

    MenuLayer() : r8ge::Layer("menuLayer") {

    }

    void update() const  {

    }

    void event(const std::shared_ptr<r8ge::Event> &event) const  {
        r8ge::event::Dispatcher dispatcher(event);
    }

    void render() const  {

    }
};

class PlainApplication : public r8ge::GameInstance {
public:
    PlainApplication() : r8ge::GameInstance("PlainApplication") {}
    ~PlainApplication() override = default;

    void onInit()  override {
        R8GE_LOG("`{}` game initialization", getGameName());

    }

    void directEvent(const std::shared_ptr<r8ge::Event> &event) override {
        r8ge::event::Dispatcher dispatcher(event);

    }

    void onUpdate() override {

    }

    void onExit()  override {
        R8GE_LOG("`{}` game exiting", getGameName());
    }
};

R8GE_ADD_INSTANCE(PlainApplication);
