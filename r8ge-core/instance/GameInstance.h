#ifndef R8GE_GAMEINSTANCE_H
#define R8GE_GAMEINSTANCE_H

#include "Instance.h"

namespace r8ge {
    class GameInstance : public Instance {
    public:
        GameInstance(const std::string& name);
        virtual ~GameInstance() override = default;

        virtual void onInit() = 0;
        virtual void onUpdate() = 0;
        virtual void onExit() = 0;

        [[nodiscard]] std::string getName() const;

    private:
        std::string m_name;
    };

    extern std::shared_ptr<r8ge::GameInstance> createGame();
}

#endif//!R8GE_GAMEINSTANCE_H
