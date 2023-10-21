#ifndef R8GE_WINDOWSINGSERVICE_H
#define R8GE_WINDOWSINGSERVICE_H

#include "../../r8ge-core/events/Strokes.h"

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <functional>

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

            void setKeyPressedCallback(std::function<void(const r8ge::IOCode&, IOAction)> callback);
            void setMousePressedCallback(std::function<void(const r8ge::IOCode&, IOAction)> callback);
        protected:
            bool m_mainWindowCreated;
            std::function<void(const r8ge::IOCode&, IOAction)> m_keyActionCallback;
            std::function<void(const r8ge::IOCode&, IOAction)> m_mouseActionCallback;
        };
    }
}

#endif//!R8GE_WINDOWSINGSERVICE_H
