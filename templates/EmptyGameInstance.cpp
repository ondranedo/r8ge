#include <r8ge/r8ge.h>

class TempalteGame : public r8ge::GameInstance {
public:
    TempalteGame() : r8ge::GameInstance("TempalteGame") {}
    ~TempalteGame() override = default;

    void onInit()  override {
        R8GE_LOG("`{}` game initialization", getGameName());
    }

    void onUpdate() override {

    }

    void onExit()  override {
        R8GE_LOG("`{}` game exiting", getGameName());
    }
};

R8GE_ADD_GAMEINSTANCE(TempalteGame);

