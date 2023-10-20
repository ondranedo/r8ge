#include "X11.h"
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

            // TODO: Add double buffering option into settings
            // TODO: Add abstraction for rendering API
            GLint attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
            auto visualInfo = glXChooseVisual(m_display, 0, attributes);

            m_visual = visualInfo;

            R8GE_ASSERT(visualInfo, "X11 Visual was failed to create");

            m_colormap = XCreateColormap(m_display, m_rootWindow, m_visual->visual, AllocNone);
            m_windowAttributes.colormap = m_colormap;
            m_windowAttributes.event_mask
                =   ExposureMask
                |   KeyPressMask
                |   KeyReleaseMask
                ;
            R8GE_LOG("X11 windowing service initialized");

            //  TODO: Create context for rendering API
            m_context = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);
            R8GE_ASSERT(m_context, "X11 Context failed to create");
            R8GE_LOG("X11 gl Context created");
        }

        void X11::release() {
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
                    m_visual->depth, InputOutput, m_visual->visual,
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

            // TODO: Move to RenderingAPI
            setContextOfMainWindow();

            R8GE_LOG_INFOR("X11 Main window `{}` created", title.data());

            // TODO: Move to RenderingAPI
            auto res = glewInit();
            if(res != GLEW_OK) {
                R8GE_LOG_ERROR("Failed to initialize GLEW: `{}`", (char *) glewGetErrorString(res));
                return false;
            }
            R8GE_LOG("GLEW initialized");

            return true;
        }

        X11::X11() : m_display(nullptr), m_rootWindow(0), m_visual(nullptr), m_colormap(0), m_windowAttributes{} {}

        void X11::poolEvents() {
            XEvent event;
            while (XPending(m_display) > 0) {
                XNextEvent(m_display, &event);

                switch (event.type) {
                    case KeyPress:
                        if(event.xkey.keycode == 9)
                            Ar8ge::stop(); // TODO: Add kill event
                        break;
                    case KeyRelease:
                        break;
                    case Expose:
                        break;
                }
            }
        }
/*
        void X11::setVSyncOnWindow(std::string_view title, bool enabled) {
            if(!isWindowPresent(title))
            {
                R8GE_LOG_WARNI("X11 Window `{}` can't be found when setting VSync", title);
                return;
            }

            // TODO: Create abstraction for rendering API
            auto glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC) glXGetProcAddress(
                    (const GLubyte *) "glXSwapIntervalEXT");
            glXSwapIntervalEXT(m_display, m_windows[title].first, enabled);
        }*/

        X11::~X11() = default;

        bool X11::destroyMainWindow() {
            if(!m_mainWindowCreated)
                return false;
            XDestroyWindow(m_display, m_mainWindow);
            m_mainWindowCreated = false;
            return true;
        }

        bool X11::setContextOfMainWindow() {
            if(!m_mainWindowCreated)
                return false;
            glXMakeContextCurrent(m_display, m_mainWindow, m_mainWindow, m_context);
            glXMakeCurrent(m_display, m_mainWindow, m_context);
            return true;
        }

        void X11::swapBuffersOfMainWindow() {
            if(!m_mainWindowCreated)
                return;

            //TODO: Add double buffering option into settings,
            //      Create abstraction for rendering API
            glXSwapBuffers(m_display, m_mainWindow);
        }
    }
}