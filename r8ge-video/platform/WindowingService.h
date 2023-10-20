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

            virtual bool createMainWindow(size_t width, size_t height, std::string_view title) = 0;
            virtual bool destroyMainWindow() = 0;
            virtual bool setContextOfMainWindow() = 0;
            virtual void swapBuffersOfMainWindow() = 0;

            virtual void poolEvents() = 0;

            static std::shared_ptr<WindowingService> create();

        protected:
            bool m_mainWindowCreated;
        };
    }
}

#endif//!R8GE_WINDOWSINGSERVICE_H
