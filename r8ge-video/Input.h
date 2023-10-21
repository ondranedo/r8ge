#ifndef R8GE_INPUT_H
#define R8GE_INPUT_H

#include <r8ge/r8ge.h>
#include <functional>
#include <unordered_map>

namespace r8ge {
    namespace video {
        class Input {
        public:
            enum Modulator {
                Shift = 0b0001,
                Ctrl  = 0b0010,
                Alt   = 0b0100,
                Super = 0b1000
            };

            friend Modulator operator | (Modulator lhs, Modulator rhs) {
                return static_cast<Modulator>(static_cast<int>(lhs) | static_cast<int>(rhs));
            }

        public:
            Input();
            ~Input();

            void sendKeyAction(const r8ge::IOCode &code, IOAction action);
            void sendMouseAction(const r8ge::IOCode &code, IOAction action);
            [[nodiscard]] std::function<void(const r8ge::IOCode&, IOAction)> getKeyActionCallback();
            [[nodiscard]] std::function<void(const r8ge::IOCode&, IOAction)> getMouseActionCallback();

            bool isShiftPressed() const;
            bool isCtrlPressed() const;
            bool isAltPressed() const;
            bool isSuperPressed() const;


            // Returns true if all keys in the list are pressed and the modulator is satisfied
            // F.e. isKeyPressed({IOCode::A, IOCode::B}, video::Input::Shift | video::Input::Ctrl) returns true if A and B are pressed and Shift and Ctrl are pressed
            bool isKeyPressed(const std::initializer_list<IOCode>& code, Modulator modulator) const;
            bool isKeyPressed(const std::initializer_list<IOCode>& code) const;
        private:
            std::unordered_map<r8ge::IOCode,bool> m_keyPressedMap;

            bool m_shiftPressed : 1;
            bool m_ctrlPressed : 1;
            bool m_altPressed : 1;
            bool m_superPressed : 1;
        };
    }
}

#endif//!R8GE_INPUT_H
