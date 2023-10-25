#ifndef R8GE_WINDOWSINGSERVICE_H
#define R8GE_WINDOWSINGSERVICE_H

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "../../r8ge-core/events/Strokes.h"

namespace r8ge {
    namespace video {
        class WindowingService {
        public:
            WindowingService();
            virtual ~WindowingService();

            virtual void init() = 0;
            virtual void exit() = 0;

            virtual bool createMainWindow(size_t width, size_t height, std::string_view title) = 0;
            virtual bool destroyMainWindow() = 0;
            virtual bool setContextOfMainWindow() = 0;
            virtual void swapBuffersOfMainWindow() = 0;

            virtual void poolEvents() = 0;

            static std::shared_ptr<WindowingService> create();

            [[nodiscard]] virtual size_t getWidthOfMainWindow() const = 0;
            [[nodiscard]] virtual size_t getHeightOfMainWindow() const = 0;

            void setKeyPressedCallback(std::function<void(const r8ge::Key&, IOAction)> callback);
            void setMousePressedCallback(std::function<void(const r8ge::Key&, IOAction)> callback);
        protected:
            bool m_mainWindowCreated;
            std::function<void(const r8ge::Key&, IOAction)> m_keyActionCallback;
            std::function<void(const r8ge::Key&, IOAction)> m_mouseActionCallback;
        };
    }
}

#endif//!R8GE_WINDOWSINGSERVICE_H
