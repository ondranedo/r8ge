#include "GameInstance.h"

#include "../Input.h"
#include "../EntryPoint.h"
#include "../Ar8ge.h"
#include "../Logger.h"
#include "../events/EngineEvents.h"
#include "../events/Event.h"
#include "../events/KeyEvents.h"

namespace r8ge {
    GameInstance::GameInstance(std::string_view name) : m_name(name) {

    }

    std::string GameInstance::getGameName() const {
        return m_name;
    }

    void GameInstance::directEvent(const std::shared_ptr<Event> &event) {
        if(Input::isKeyPressed(Key::ESCAPE)) {
            R8GE_LOG_DEBUG("Escape pressed, exiting");
            r8ge::Ar8ge::killEngine();
        }
    }
}