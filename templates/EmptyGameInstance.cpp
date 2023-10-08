// Includes may cause problems, make sure to include them properly
// one include file is not yet written

#include "../r8ge-core/Core.h"
#include "../r8ge-core/instance/GameInstance.h"
#include "../r8ge-core/Logger.h"

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

