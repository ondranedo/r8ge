#include "Input.h"

#include <utility>
#include <r8ge/r8ge.h>

namespace r8ge {

    video::Input::Input() : m_shiftPressed(false), m_ctrlPressed(false), m_altPressed(false), m_superPressed(false) {}
    video::Input::~Input() = default;

    void video::Input::sendKeyAction(const IOCode &code, IOAction action) {
        if(code==IOCode::LEFT_SHIFT||code==IOCode::RIGHT_SHIFT) m_shiftPressed = (action == IOAction::PRESS);
        if(code==IOCode::LEFT_ALT||code==IOCode::RIGHT_ALT) m_altPressed = (action == IOAction::PRESS);
        if(code==IOCode::LEFT_CONTROL||code==IOCode::RIGHT_CONTROL) m_ctrlPressed = (action == IOAction::PRESS);
        if(code==IOCode::LEFT_SUPER||code==IOCode::RIGHT_SUPER) m_superPressed = (action == IOAction::PRESS);

        m_keyPressedMap[code] = (action == IOAction::PRESS);
    }

    std::function<void(const r8ge::IOCode &, IOAction)> video::Input::getKeyActionCallback() {
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

    bool video::Input::isKeyPressed(const std::initializer_list<IOCode>& code, video::Input::Modulator modulator) const {
        if(modulator & Modulator::Shift && !m_shiftPressed) return false;
        if(modulator & Modulator::Ctrl && !m_ctrlPressed) return false;
        if(modulator & Modulator::Alt && !m_altPressed) return false;
        if(modulator & Modulator::Super && !m_superPressed) return false;
        return isKeyPressed(code);
    }

    bool video::Input::isKeyPressed(const std::initializer_list<IOCode>& code) const {
        for(auto & c : code)
        {
            if(c == IOCode::RIGHT_SHIFT || c == IOCode::LEFT_SHIFT || c== IOCode::RIGHT_CONTROL || c == IOCode::LEFT_CONTROL || c == IOCode::RIGHT_ALT || c == IOCode::LEFT_ALT || c == IOCode::RIGHT_SUPER || c == IOCode::LEFT_SUPER ) {
                R8GE_LOG_WARNI("Invalid key code, use Modulator instead");
                return false;
            }
            if(m_keyPressedMap.find(c) == m_keyPressedMap.end()) return false;
            if(!m_keyPressedMap.at(c)) return false;
        }
        return true;
    }
}