#ifndef R8GE_WINDOWSINGSERVICE_H
#define R8GE_WINDOWSINGSERVICE_H

#include <cstddef>
#include <string>
#include <vector>
#include <memory>


namespace r8ge {
    namespace video {
        class WindowingService {
        public:
            WindowingService();
            virtual ~WindowingService();

            virtual void init() = 0;
            virtual void release() = 0;

            virtual bool createWindow(size_t width, size_t height, std::string_view title) = 0;

            virtual void poolEvents() = 0;

            virtual void swapBuffersOfWindow(std::string_view title) = 0;
            virtual bool showWindow(std::string_view title) = 0;
            virtual bool hideWindow(std::string_view title) = 0;
            virtual bool destroyWindow(std::string_view title) = 0;
            virtual void setContextOfWindow(std::string_view title) = 0;
            virtual void setVSyncOnWindow(std::string_view title, bool enabled) = 0;
            virtual void updateWindows() = 0;

            static std::shared_ptr<WindowingService> create();
        protected:
            size_t m_windowCount;
        };
    }
}

#endif//!R8GE_WINDOWSINGSERVICE_H
