#include "GameInstance.h"

namespace r8ge {
    GameInstance::GameInstance(std::string_view name) : m_name(name) {

    }

    std::string GameInstance::getGameName() const {
        return m_name;
    }
}