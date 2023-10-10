#include "GameInstance.h"

namespace r8ge {
    GameInstance::GameInstance(const std::string &name) : m_name(name) {

    }

    std::string GameInstance::getGameName() const {
        return m_name;
    }
}