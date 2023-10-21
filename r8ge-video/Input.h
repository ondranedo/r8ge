#ifndef R8GE_INPUT_H
#define R8GE_INPUT_H
#include <functional>
#include <unordered_map>

#include "../r8ge-core/events/Strokes.h"

namespace r8ge {
    namespace video {
        class Input {
        public:
            Input();
            ~Input();

            void sendKeyAction(const r8ge::Code &code, IOAction action);
            void sendMouseAction(const r8ge::Code &code, IOAction action);
            [[nodiscard]] std::function<void(const r8ge::Code&, IOAction)> getKeyActionCallback();
            [[nodiscard]] std::function<void(const r8ge::Code&, IOAction)> getMouseActionCallback();

            bool isShiftPressed() const;
            bool isCtrlPressed() const;
            bool isAltPressed() const;
            bool isSuperPressed() const;


            // Returns true if all keys in the list are pressed and the modulator is satisfied
            // F.e. isKeyPressed({IOCode::A, IOCode::B}, video::Input::Shift | video::Input::Ctrl) returns true if A and B are pressed and Shift and Ctrl are pressed
            bool isKeyPressed(const std::initializer_list<Code>& code, Modifier modifier) const;
            bool isKeyPressed(const std::initializer_list<Code>& code) const;
        private:
            std::unordered_map<r8ge::Code,bool> m_keyPressedMap;

            bool m_shiftPressed : 1;
            bool m_ctrlPressed : 1;
            bool m_altPressed : 1;
            bool m_superPressed : 1;
        };
    }
}

#endif//!R8GE_INPUT_H
