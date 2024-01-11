#include "GLFW.h"

#include "../../WindowingService.h"
#include <GLFW/glfw3.h>
#include "Convertor.h"
#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        std::shared_ptr<WindowingService> WindowingService::create() {
            return std::make_shared<GLFW>();
        }

        void GLFW::init() {
            if (!glfwInit()) {
                R8GE_LOG_ERROR("Unable to init GLFW");
            }
            else {
                R8GE_LOG("GLFW Initialized running version `{}`", glfwGetVersionString());
            }

        }

        void GLFW::exit() {
            if (m_mainWindowCreated)
                destroyMainWindow();
            R8GE_LOG("GLFW windowing service released");
        }

        bool GLFW::createMainWindow(size_t width, size_t height, std::string title) {
            R8GE_LOG("GLFW Window is being creating `{}`", title);

            m_mainWindow = glfwCreateWindow(
                    static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

            if (!m_mainWindow) {
                R8GE_LOG_ERROR("GLFW Main window `{}` failed to create", title);
                return false;
            }

            m_mainWindowCreated = true;
            m_mainWindowHeight = height;
            m_mainWindowWidth = width;

            R8GE_LOG_INFOR("GLFW Main window `{}` created", title.data());

            //m_xContext->setWindow(m_mainWindow);
            //m_xContext->windowIsReady();

            return true;
        }

        void GLFW::poolEvents() {
            glfwPollEvents();
        }

        void GLFW::setEventCallbacks() {
            glfwSetWindowUserPointer(m_mainWindow, this);

            glfwSetKeyCallback(m_mainWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    Key code = GLFWConvertor::convertKeyCode(key);

                    switch (action) {
                        case GLFW_PRESS:
                            instance->m_keyActionCallback(code, IOAction::PRESS);
                            break;
                        case GLFW_RELEASE:
                            instance->m_keyActionCallback(code, IOAction::RELEASE);
                            break;
                            /* TODO Add Repeat ??
                        case GLFW_REPEAT:
                            instance->m_keyActionCallback(code, IOAction::REPEAT);
                            break;
                             */
                        default:
                            break;
                    }

                }
            });

            glfwSetMouseButtonCallback(m_mainWindow, [](GLFWwindow *window, int button, int action, int mods) {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    Key code = GLFWConvertor::convertKeyCode(button);

                    switch (action) {
                        case GLFW_PRESS:
                            instance->m_keyActionCallback(code, IOAction::PRESS);
                            break;
                        case GLFW_RELEASE:
                            instance->m_keyActionCallback(code, IOAction::RELEASE);
                            break;
                        default:
                            break;
                    }
                }
            });

            glfwSetCursorPosCallback(m_mainWindow, [](GLFWwindow *window, double xpos, double ypos) {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    p.setEvent(std::make_shared<MouseMoved>(xpos, ypos));
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });

            glfwSetScrollCallback(m_mainWindow, [](GLFWwindow *window, double xOffset, double yOffset) -> void {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    p.setEvent(std::make_shared<MouseScrolled>(xOffset, yOffset));
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });

            glfwSetWindowSizeCallback(m_mainWindow, windowSizeCallback);

            glfwSetWindowCloseCallback(m_mainWindow, [](GLFWwindow *window) -> void {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    p.setEvent(std::make_shared<WindowClosed>());
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });

            glfwSetWindowFocusCallback(m_mainWindow, [](GLFWwindow *window, int focused) -> void {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    if (focused) {
                        p.setEvent(std::make_shared<WindowFocus>());
                    }
                    else {
                        p.setEvent(std::make_shared<WindowLostFocus>());
                    }
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });
        }


        GLFW::~GLFW() {
            glfwTerminate();
        }

        bool GLFW::destroyMainWindow() {
            if (!m_mainWindowCreated)
                return false;
            glfwDestroyWindow(m_mainWindow);
            m_mainWindowCreated = false;
            return true;
        }

        bool GLFW::setContextOfMainWindow() {
            glfwMakeContextCurrent(m_mainWindow);
            return true;
        }

        void GLFW::swapBuffersOfMainWindow() {
            if (!m_mainWindowCreated)
                return;

            glfwSwapBuffers(m_mainWindow);
        }

        void GLFW::windowSizeCallback(GLFWwindow *window, int width, int height) {
            GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

            if (instance) {
                instance->m_mainWindowWidth = width;
                instance->m_mainWindowHeight = height;

                EventPayload p;
                p.setEvent(std::make_shared<WindowResized>(width, height));
                p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                Ar8ge::getEventQueue()(p);

                //instance->m_xContext->windowChanged(instance->m_mainWindowWidth, instance->m_mainWindowHeight);
            }
        }

    }
}