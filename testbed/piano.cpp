//
// Created by apostrophenome on 24.10.23.
//
#include <r8ge/r8ge.h>
#include <r8ge/video.h>
#include <r8ge/sound.h>

#include <memory>

double testgen(double time) {
    return
    std::sin(time) +
    (0.5 * std::sin(2 * time))  * r8ge::square(8 * time);
}

class GameLayer : public r8ge::Layer {
    bool state = false;
    // todo: too dumb to move outside of hfere
    r8ge::AudioPusher sound;

    // piano --------------------------------------
    static const int keyCount = 17;
    const r8ge::Key keyboard[keyCount] = {
            r8ge::Key::A,
            r8ge::Key::W,
            r8ge::Key::S,
            r8ge::Key::E,
            r8ge::Key::D,
            r8ge::Key::F,
            r8ge::Key::T,
            r8ge::Key::G,
            r8ge::Key::Y,
            r8ge::Key::H,
            r8ge::Key::U,
            r8ge::Key::J,
            r8ge::Key::K,
            r8ge::Key::O,
            r8ge::Key::L,
            r8ge::Key::P,
            r8ge::Key::SEMICOLON,
    };
    int ids[keyCount] = {-1};
    bool wasPressed[keyCount] = {false};
    bool isPlaying[keyCount] = {false};
    void pianoUpdate(){
        // resetting the keys
        for (bool & i : wasPressed) {
            i = false;
        }
        // checking the pressed keys
        for(int i = 0; i < keyCount; i++) {
            if(r8ge::Input::isKeyPressed(keyboard[i])){
                wasPressed[i] = true;
            }
        }
        // starting or stopping keys
        for (int i = 0; i < keyCount; i++) {
            if (wasPressed[i]) {
                if (!isPlaying[i]) {
                    ids[i] = sound.playNote(20 + i, r8ge::saw);
                    isPlaying[i] = true;
                }
            }
            else {
                if (isPlaying[i]) {
                    sound.deleteSound(ids[i]);
                    isPlaying[i] = false;
                }
            }
        }
    }
    // -------------------------------------------------------------
public:
    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

    }

    void update() override {

    }

    void event(const std::shared_ptr<r8ge::Event> &event) override {
        pianoUpdate();
    }

    void render() override {

    }
};

class PlainApp : public r8ge::GameInstance {

public:
    PlainApp() : r8ge::GameInstance("testbedGame") {}
    ~PlainApp() override = default;

    void onInit()  override {
        R8GE_LOG("`{}` game initialization", getGameName());

        layerSwitcher().add<GameLayer>();
    }

    void onUpdate() override {

    }

    void onExit()  override {
        R8GE_LOG("`{}` game exiting", getGameName());
    }
};

R8GE_ADD_INSTANCE(PlainApp);