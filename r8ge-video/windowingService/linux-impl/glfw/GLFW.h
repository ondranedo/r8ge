#ifndef R8GE_X11_H
#define R8GE_X11_H

#include <tuple>
#include <cstddef>
#include <unordered_map>

#include <GLFW/glfw3.h>


#include "../../WindowingService.h"



namespace r8ge {
    namespace video {
        class GLFW : public WindowingService {
        public:
            ~GLFW() override;
            void init() override;
            void exit() override;
            bool createMainWindow(size_t width, size_t height, std::string title) override;

            void poolEvents() override;
            bool destroyMainWindow() override;
            void setEventCallbacks() override;
            bool setContextOfMainWindow() override;
            void swapBuffersOfMainWindow() override;

            static void windowSizeCallback(GLFWwindow* window, int width, int height);

        private:
            size_t m_mainWindowWidth, m_mainWindowHeight;
            std::string m_mainWindowTitle;

            GLFWwindow* m_mainWindow;

        };
    }
}

#endif//!R8GE_X11_H
