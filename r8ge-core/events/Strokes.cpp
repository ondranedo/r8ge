#include "Strokes.h"

namespace r8ge {
    std::string to_string(const Code& code) {
        switch (code) {
            case Code::UNKNOWN: return "unknown";
            case Code::MBUTTON_1: return "mouse 1";
            case Code::MBUTTON_2: return "mouse 2";
            case Code::MBUTTON_3: return "mouse 3";
            case Code::MBUTTON_4: return "mouse 4";
            case Code::MBUTTON_5: return "mouse 5";
            case Code::MBUTTON_6: return "mouse 6";
            case Code::MBUTTON_7: return "mouse 7";
            case Code::MBUTTON_8: return "mouse 8";
            case Code::MBUTTON_LEFT: return "mouse left";
            case Code::MBUTTON_RIGHT: return "mouse right";
            case Code::MBUTTON_MIDDLE: return "mouse middle";
            case Code::SPACE: return "space";
            case Code::APOSTROPHE: return "\'";
            case Code::COMMA: return ",";
            case Code::MINUS: return "-";
            case Code::PERIOD: return ".";
            case Code::SLASH: return "/";
            case Code::N0: return "0";
            case Code::N1: return "1";
            case Code::N2: return "2";
            case Code::N3: return "3";
            case Code::N4: return "4";
            case Code::N5: return "5";
            case Code::N6: return "6";
            case Code::N7: return "7";
            case Code::N8: return "8";
            case Code::N9: return "9";
            case Code::SEMICOLON: return ";";
            case Code::EQUAL: return "=";
            case Code::A: return "A";
            case Code::B: return "B";
            case Code::C: return "C";
            case Code::D: return "D";
            case Code::E: return "E";
            case Code::F: return "F";
            case Code::G: return "G";
            case Code::H: return "H";
            case Code::I: return "I";
            case Code::J: return "J";
            case Code::K: return "K";
            case Code::L: return "L";
            case Code::M: return "M";
            case Code::N: return "N";
            case Code::O: return "O";
            case Code::P: return "P";
            case Code::Q: return "Q";
            case Code::R: return "R";
            case Code::S: return "S";
            case Code::T: return "T";
            case Code::U: return "U";
            case Code::V: return "V";
            case Code::W: return "W";
            case Code::X: return "X";
            case Code::Y: return "Y";
            case Code::Z: return "Z";
            case Code::LEFT_BRACKET: return "[";
            case Code::BACKSLASH: return "\\";
            case Code::RIGHT_BRACKET: return "]";
            case Code::GRAVE_ACCENT: return "`";
            case Code::ESCAPE: return "ESC";
            case Code::ENTER: return "enter";
            case Code::TAB: return "tab";
            case Code::BACKSPACE: return "backspace";
            case Code::INSERT: return "insert";
            case Code::DELETE: return "delete";
            case Code::RIGHT: return "right";
            case Code::LEFT: return "left";
            case Code::DOWN: return "down";
            case Code::UP: return "up";
            case Code::PAGE_UP: return "page up";
            case Code::PAGE_DOWN: return "page down";
            case Code::HOME: return "home";
            case Code::END: return "end";
            case Code::CAPS_LOCK: return "caps lock";
            case Code::SCROLL_LOCK: return "scroll lock";
            case Code::NUM_LOCK: return "num lock";
            case Code::PRINT_SCREEN: return "print screen";
            case Code::PAUSE: return "pause";
            case Code::F1: return "F1";
            case Code::F2: return "F2";
            case Code::F3: return "F3";
            case Code::F4: return "F4";
            case Code::F5: return "F5";
            case Code::F6: return "F6";
            case Code::F7: return "F7";
            case Code::F8: return "F8";
            case Code::F9: return "F9";
            case Code::F10: return "F10";
            case Code::F11: return "F11";
            case Code::F12: return "F12";
            case Code::F13: return "F13";
            case Code::F14: return "F14";
            case Code::F15: return "F15";
            case Code::F16: return "F16";
            case Code::F17: return "F17";
            case Code::F18: return "F18";
            case Code::F19: return "F19";
            case Code::F20: return "F20";
            case Code::F21: return "F21";
            case Code::F22: return "F22";
            case Code::F23: return "F23";
            case Code::F24: return "F24";
            case Code::F25: return "F25";
            case Code::KP_0: return "KP 0";
            case Code::KP_1: return "KP 1";
            case Code::KP_2: return "KP 2";
            case Code::KP_3: return "KP 3";
            case Code::KP_4: return "KP 4";
            case Code::KP_5: return "KP 5";
            case Code::KP_6: return "KP 6";
            case Code::KP_7: return "KP 7";
            case Code::KP_8: return "KP 8";
            case Code::KP_9: return "KP 9";
            case Code::KP_DECIMAL: return "KP decimal";
            case Code::KP_DIVIDE: return "KP divide";
            case Code::KP_MULTIPLY: return "KP multiply";
            case Code::KP_SUBTRACT: return "KP subtract";
            case Code::KP_ADD: return "KP add";
            case Code::KP_ENTER: return "KP enter";
            case Code::KP_EQUAL: return "KP equal";
            case Code::LEFT_SHIFT: return "left shift";
            case Code::LEFT_CONTROL: return "left control";
            case Code::LEFT_ALT: return "left alt";
            case Code::LEFT_SUPER: return "left super";
            case Code::RIGHT_SHIFT: return "right shift";
            case Code::RIGHT_CONTROL: return "right control";
            case Code::RIGHT_ALT: return "right alt";
            case Code::RIGHT_SUPER: return "right super";
            case Code::MENU: return "menu";
        }
        return "unknown";
    }

    std::string to_string(Modifier action) {
        std::string ret;

        if(action==Modifier::NONE) ret+="none";
        if(action&Modifier::SHIFT) ret+="shift";
        if(action&Modifier::CTRL)  ret+="control";
        if(action&Modifier::ALT)   ret+="alt";
        if(action&Modifier::SUPER) ret+="super";

        return ret;
    }

    Modifier operator|(Modifier lhs, Modifier rhs) {
        return static_cast<Modifier>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    bool operator&(Modifier lhs, Modifier rhs) {
        return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));
    }
}