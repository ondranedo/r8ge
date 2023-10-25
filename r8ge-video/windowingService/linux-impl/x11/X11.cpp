#include "X11.h"
#include "Convertor.h"
#include "../../WindowingService.h"


#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        std::shared_ptr<WindowingService> WindowingService::create() {
            return std::make_shared<X11>();
        }

        void X11::init() {

            m_display = XOpenDisplay(nullptr);
            R8GE_ASSERT(m_display, "X11 display was failed to open");

            R8GE_LOG_DEBUG("X11 display: {}x{}", XDisplayWidth(m_display, 0), XDisplayHeight(m_display, 0));

            m_rootWindow = DefaultRootWindow(m_display);

            m_xContext = video::XContext::create();
            m_xContext->setDisplay(m_display);
            m_xContext->init();

            auto colormap = XCreateColormap(m_display, m_rootWindow, m_xContext->getVisualInfo()->visual, AllocNone);//*
            m_windowAttributes.colormap = colormap;
            m_windowAttributes.event_mask = ExposureMask;
            R8GE_LOG("X11 windowing service initialized");

            m_xContext->createContext();
        }

        void X11::exit() {
            m_xContext->exit();
            if(m_mainWindowCreated)
                destroyMainWindow();
            R8GE_LOG("X11 windowing service released");
        }

        bool X11::createMainWindow(size_t width, size_t height, std::string_view title) {
            R8GE_LOG("X11 Window is being creating `{}`", title);

            m_mainWindow = XCreateWindow(
                    m_display, m_rootWindow,
                    0, 0,
                    width, height,
                    0,
                    m_xContext->getVisualInfo()->depth, InputOutput, m_xContext->getVisualInfo()->visual,//*
                    CWColormap | CWEventMask,
                    &m_windowAttributes);

            if(!m_mainWindow)
            {
                R8GE_LOG_ERROR("X11 Main window `{}` failed to create", title);
                return false;
            }

            XStoreName(m_display, m_mainWindow, title.data());
            XMapWindow(m_display, m_mainWindow);
            m_mainWindowTitle = title;
            m_mainWindowCreated = true;
            m_mainWindowHeight = height;
            m_mainWindowWidth = width;

            R8GE_LOG_INFOR("X11 Main window `{}` created", title.data());

            m_xContext->setWindow(m_mainWindow);
            m_xContext->windowIsReady();

            return true;
        }

        X11::X11() : m_display(nullptr), m_rootWindow(0), m_windowAttributes{} {}

        void X11::poolEvents() {
            XEvent event;
            XSelectInput(m_display, m_mainWindow, ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);

            while (XPending(m_display) > 0) {
                XNextEvent(m_display, &event);

                switch (event.type) {
                    case KeyPress: {
                        Key code = X11Convertor::convertKeyCode(event.xkey.keycode);
                        m_keyActionCallback(code, IOAction::PRESS);
                        break;
                    } case KeyRelease: {
                        Key code = X11Convertor::convertKeyCode(event.xkey.keycode);
                        m_keyActionCallback(code, IOAction::RELEASE);
                        break;
                    } case MotionNotify: {
                        EventPayload p;
                        p.setEvent(std::make_shared<MouseMoved>(event.xmotion.x, event.xmotion.y));
                        p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                        Ar8ge::getEventQueue()(p);
                        break;
                    } case ButtonPress: {
                        Key code = X11Convertor::convertKeyCode((event.xbutton.button) << 8);
                        m_mouseActionCallback(code, IOAction::PRESS);
                        break;
                    } case ButtonRelease: {
                        Key code = X11Convertor::convertKeyCode((event.xbutton.button) << 8);
                        m_mouseActionCallback(code, IOAction::RELEASE);
                        break;
                    } case Expose: {
                        m_mainWindowHeight = event.xexpose.height;
                        m_mainWindowWidth = event.xexpose.width;

                        EventPayload p;
                        p.setEvent(std::make_shared<WindowResized>(m_mainWindowWidth, m_mainWindowHeight));
                        p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                        Ar8ge::getEventQueue()(p);

                        m_xContext->windowChanged(m_mainWindowWidth, m_mainWindowHeight);

                        break;
                    }
                    default: {
                        R8GE_LOG_DEBUG("X11 Event: `{}`", event.type);
                    }
                }
            }
        }

        X11::~X11() = default;

        bool X11::destroyMainWindow() {
            if(!m_mainWindowCreated)
                return false;
            XDestroyWindow(m_display, m_mainWindow);
            m_mainWindowCreated = false;
            return true;
        }

        bool X11::setContextOfMainWindow() {
            m_xContext->setContextActive();
            return true;
        }

        void X11::swapBuffersOfMainWindow() {
            if(!m_mainWindowCreated)
                return;

            m_xContext->swapBuffers();
        }

        size_t X11::getWidthOfMainWindow() const {
            return m_mainWindowWidth;
        }

        size_t X11::getHeightOfMainWindow() const {
            return m_mainWindowHeight;
        }
    }
}