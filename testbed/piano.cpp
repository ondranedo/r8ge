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
    r8ge::Instrument test = {{}, testgen};

    static const int keyCount = 17;
    bool sw = 0;

    int ids[keyCount] = {-1};
    bool wasPressed[keyCount] = {false};
    bool isPlaying[keyCount] = {false};
public:
    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

    }

    void update() override {

    }

    void event(const std::shared_ptr<r8ge::Event> &event) override {
        for (int i = 0; i < keyCount; i++) {
            wasPressed[i] = false;
        }
        r8ge::ColorRGB color(0x000000);

        if (r8ge::Input::isKeyPressed(r8ge::Key::A)) {
            wasPressed[0] = true;
            //
            color.r += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::W)) {
            wasPressed[1] = true;
            color.g += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::S)) {
            wasPressed[2] = true;
            color.b += 0x20;

        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::E)) {
            wasPressed[3] = true;
            color.r += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::D)) {
            wasPressed[4] = true;
            color.g += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::F)) {
            wasPressed[5] = true;
            color.b += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::T)) {
            wasPressed[6] = true;
            color.r += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::G)) {
            wasPressed[7] = true;
            color.g += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::Z)) {
            wasPressed[8] = true;
            color.b += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::H)) {
            wasPressed[9] = true;
            color.r += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::U)) {
            wasPressed[10] = true;
            color.g += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::J)) {
            wasPressed[11] = true;
            color.b += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::K)) {
            wasPressed[12] = true;
            color.r += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::O)) {
            wasPressed[13] = true;
            color.b += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::L)) {
            wasPressed[14] = true;
            color.r += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::P)) {
            wasPressed[15] = true;
            color.g += 0x20;
        }
        if (r8ge::Input::isKeyPressed(r8ge::Key::SEMICOLON)) {
            wasPressed[16] = true;
        }

        r8ge::Video::getRenderingService()->setClearColor(color);

        for (int i = 0; i < keyCount; i++) {
            if (wasPressed[i]) {
                if (!isPlaying[i]) {
                    //ids[i] = sound.playNote(40 + i, sw ? test : );
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