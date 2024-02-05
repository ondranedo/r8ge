//
// Created by apostrophenome on 24.10.23.
//
#include <r8ge/r8ge.h>
#include <r8ge/video.h>
#include <r8ge/sound.h>

#include <memory>

class GameLayer : public r8ge::Layer {
    bool state = false;
    // todo: too dumb to move outside of here
    r8ge::AudioPusher sound;
    r8ge::Instrument test;

    static const int keyCount = 17;

    int ids[keyCount] = {-1};
    bool wasPressed[keyCount] = {false};
    bool isPlaying[keyCount] = {false};
public:
    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

    }

    void update() override {

    }

    void event(const std::shared_ptr<r8ge::Event> &event) override{
        for(int i = 0; i < keyCount; i++){
            wasPressed[i] = false;
        }

        if(r8ge::Input::isKeyPressed(r8ge::Key::A)) {
            wasPressed[0] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::W)) {
            wasPressed[1] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::S)) {
            wasPressed[2] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::E)) {
            wasPressed[3] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::D)) {
            wasPressed[4] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::F)) {
            wasPressed[5] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::T)) {
            wasPressed[6] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::G)) {
            wasPressed[7] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::Z)) {
            wasPressed[8] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::H)) {
            wasPressed[9] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::U)) {
            wasPressed[10] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::J)) {
            wasPressed[11] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::K)) {
            wasPressed[12] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::O)) {
            wasPressed[13] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::L)) {
            wasPressed[14] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::P)) {
            wasPressed[15] = true;
        }
        if(r8ge::Input::isKeyPressed(r8ge::Key::SEMICOLON)) {
            wasPressed[16] = true;
        }

        for(int i = 0; i < keyCount; i++){
            if(wasPressed[i]){
                if(!isPlaying[i]){
                    ids[0] = sound.playNote(40 + i, test);
                    isPlaying[i] = true;
                }
            }
            else{
                if(isPlaying[i]){
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