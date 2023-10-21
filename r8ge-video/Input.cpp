#include "Input.h"

#include <utility>
#include <r8ge/r8ge.h>

namespace r8ge {

    video::Input::Input() : m_shiftPressed(false), m_ctrlPressed(false), m_altPressed(false), m_superPressed(false) {}
    video::Input::~Input() = default;

    void video::Input::sendKeyAction(const Code &code, IOAction action) {
        if(code == Code::LEFT_SHIFT || code == Code::RIGHT_SHIFT) m_shiftPressed = (action == IOAction::PRESS);
        if(code == Code::LEFT_ALT || code == Code::RIGHT_ALT) m_altPressed = (action == IOAction::PRESS);
        if(code == Code::LEFT_CONTROL || code == Code::RIGHT_CONTROL) m_ctrlPressed = (action == IOAction::PRESS);
        if(code == Code::LEFT_SUPER || code == Code::RIGHT_SUPER) m_superPressed = (action == IOAction::PRESS);

        m_keyPressedMap[code] = (action == IOAction::PRESS);

        EventPayload payload;
        payload.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
        IOStroke stroke = {code, m_shiftPressed, m_ctrlPressed, m_altPressed, m_superPressed};
        if(action == IOAction::PRESS)
            payload.setEvent(std::make_shared<KeyPressed>(stroke, false));
        else
            payload.setEvent(std::make_shared<KeyReleased>(stroke));
        Ar8ge::getEventQueue()(payload);
    }

    void video::Input::sendMouseAction(const Code &code, IOAction action) {
        m_keyPressedMap[code] = (action == IOAction::PRESS);

        EventPayload payload;
        payload.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
        IOStroke stroke = {code, m_shiftPressed, m_ctrlPressed, m_altPressed, m_superPressed};
        if(action == IOAction::PRESS)
            payload.setEvent(std::make_shared<MousePressed>(stroke));
        else
            payload.setEvent(std::make_shared<MouseReleased>(stroke));
        Ar8ge::getEventQueue()(payload);
    }

    std::function<void(const r8ge::Code &, IOAction)> video::Input::getMouseActionCallback() {
        return [this](auto && PH1, auto && PH2) { sendMouseAction(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); };
    }

    std::function<void(const r8ge::Code &, IOAction)> video::Input::getKeyActionCallback() {
        return [this](auto && PH1, auto && PH2) { sendKeyAction(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); };
    }

    bool video::Input::isShiftPressed() const {
        return m_shiftPressed;
    }

    bool video::Input::isCtrlPressed() const {
        return m_ctrlPressed;
    }

    bool video::Input::isAltPressed() const {
        return m_altPressed;
    }

    bool video::Input::isSuperPressed() const {
        return m_superPressed;
    }

    bool video::Input::isKeyPressed(const std::initializer_list<Code>& code, Modifier modifier) const {
        if(modifier & Modifier::SHIFT && !m_shiftPressed) return false;
        if(modifier & Modifier::CTRL && !m_ctrlPressed)   return false;
        if(modifier & Modifier::ALT && !m_altPressed)     return false;
        if(modifier & Modifier::SUPER && !m_superPressed) return false;
        R8GE_LOG("Checking key: {}", to_string(modifier));
        return isKeyPressed(code);
    }

    bool video::Input::isKeyPressed(const std::initializer_list<Code>& code) const {
        for(auto & c : code)
        {
            if(c == Code::RIGHT_SHIFT || c == Code::LEFT_SHIFT || c == Code::RIGHT_CONTROL || c == Code::LEFT_CONTROL || c == Code::RIGHT_ALT || c == Code::LEFT_ALT || c == Code::RIGHT_SUPER || c == Code::LEFT_SUPER ) {
                R8GE_LOG_WARNI("Invalid key code, use Modulator instead");
                return false;
            }
            if(m_keyPressedMap.find(c) == m_keyPressedMap.end()) return false;
            if(!m_keyPressedMap.at(c)) return false;
        }
        return true;
    }
}