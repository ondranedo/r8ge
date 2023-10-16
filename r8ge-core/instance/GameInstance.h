#ifndef R8GE_GAMEINSTANCE_H
#define R8GE_GAMEINSTANCE_H

#include "Instance.h"

namespace r8ge {

    // The main game instance, handles the layers, and the logic,
    // TODO: for now, there can be only one instance of the game, this will be changed in the future
    class GameInstance : public Instance {
    public:
        explicit GameInstance(std::string_view name);
        virtual ~GameInstance() override = default;

        // Called when class is initialized, not created!
        virtual void onInit() = 0;

        // Called evert frame, main core game logic should be here, not the rendering!
        // Rendering should be handled by the layers
        virtual void onUpdate() = 0;

        // Called when the class is destroyed, not deleted!
        virtual void onExit() = 0;

        [[nodiscard]] std::string getGameName() const;

    private:
        std::string m_name;
    };

    extern std::shared_ptr<r8ge::GameInstance> createGame();
}

#define R8GE_ADD_GAMEINSTANCE(x) namespace r8ge {std::shared_ptr<r8ge::GameInstance> createGame() {return std::make_shared<x>();}}

#endif//!R8GE_GAMEINSTANCE_H
