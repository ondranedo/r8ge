#ifndef R8GE_WINDOWSINGSERVICE_H
#define R8GE_WINDOWSINGSERVICE_H

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

#include "../Window.h"

namespace r8ge {
    namespace video {
        class WindowingService {
        public:
            WindowingService();
            virtual ~WindowingService();

            virtual void init() = 0;
            virtual void release() = 0;

            virtual bool createWindow(const Window::Dims& dims, std::string_view title) = 0;

            virtual void poolEvents() = 0;

            virtual void swapBuffersOfWindow(std::string_view title) = 0;
            virtual bool showWindow(std::string_view title) = 0;
            virtual bool hideWindow(std::string_view title) = 0;
            virtual bool destroyWindow(std::string_view title) = 0;
            virtual void setContextOfWindow(std::string_view title) = 0;
            virtual void setVSyncOnWindow(std::string_view title, bool enabled) = 0;
            virtual void updateWindows() = 0;

            static std::shared_ptr<WindowingService> create();
            [[nodiscard]] static WindowingService& getService();
            static void releaseService();
            static void setActiveService(const std::shared_ptr<WindowingService>& service);
        protected:
            static std::shared_ptr<WindowingService> s_activeService;
            size_t m_windowCount;
        };
    }
}

#endif//!R8GE_WINDOWSINGSERVICE_H
