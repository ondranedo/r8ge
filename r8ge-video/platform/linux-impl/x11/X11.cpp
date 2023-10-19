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
            R8GE_ASSERT(m_display, "Failed to open X11 display");

            m_rootWindow = DefaultRootWindow(m_display);

            // TODO: Add double buffering option into settings
            // TODO: Add abstraction for rendering API
            GLint attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
            auto visualInfo = glXChooseVisual(m_display, 0, attributes);\

            m_depth = visualInfo->depth;
            m_visual = visualInfo;

            R8GE_ASSERT(visualInfo, "Failed to create X11 visual");

            m_colormap = XCreateColormap(m_display,m_rootWindow, m_visual->visual, AllocNone);
            m_windowAttributes.colormap = m_colormap;
            m_windowAttributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;

            R8GE_LOG("X11 windowing service initialized");

            //  TODO: Create context for rendering API
            m_context = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);
            R8GE_ASSERT(m_context, "Failed to create X11 context");
        }

        void X11::release() {
            R8GE_LOG("X11 windowing service released");
        }

        bool X11::createWindow(const Window::Dims &dims, std::string_view title) {
            ::Window win = XCreateWindow(
                    m_display, m_rootWindow,
                    0, 0,
                    dims.first, dims.second,
                    0,
                    m_depth, InputOutput, m_visual->visual,
                    CWColormap | CWEventMask,
                    &m_windowAttributes);

            if(!win)
            {
                R8GE_LOG_ERROR("Failed to create X11 window");
                return false;
            }

            XStoreName(m_display, win, title.data());
            XMapWindow(m_display, win);

            m_windows[title] = {win, false};
            m_windowCount++;

            //  TODO: Move to RenderingAPI
            glXMakeCurrent(m_display, win, m_context);


            setContextOfWindow(title);

            //  TODO: Move to RenderingAPI
            auto res = glewInit();
            R8GE_ASSERT(res == GLEW_OK,"Failed to initialize GLEW: {}", (char*)glewGetErrorString(res));


            R8GE_LOG_INFOR("Created X11 window: {}", title.data());
            m_windows[title].second = true;
            return true;
        }

        bool X11::showWindow(std::string_view title) {
            if(!m_windows.contains(title))
            {
                R8GE_LOG_ERROR("Failed to show X11 window: window not found");
                return false;
            }

            XMapWindow(m_display, m_windows[title].first);
            return true;
        }

        bool X11::hideWindow(std::string_view title) {
            return false;
        }

        bool X11::destroyWindow(std::string_view title) {
            return false;
        }

        X11::X11() : m_display(nullptr), m_rootWindow(0), m_visual(nullptr), m_colormap(0), m_depth(0), m_windowAttributes{} {}

        void X11::poolEvents() {
            XEvent event;
            while (XPending(m_display) > 0) {
                XNextEvent(m_display, &event);

                switch (event.type) {
                    case Expose:
                        break;
                    case KeyPress:
                        if(XLookupKeysym(&event.xkey, 0)==65307) {
                            global::ar8geRunning = false;
                        }
                        break;
                    case KeyRelease:
                        break;
                    default:
                        break;
                }
            }
        }

        void X11::swapBuffersOfWindow(std::string_view title) {

            //TODO: Add double buffering option into settings,
            //      Create abstraction for rendering API
            glXSwapBuffers(m_display, m_windows[title].first);
        }

        void X11::setVSyncOnWindow(std::string_view title, bool enabled) {

            // TODO: Create abstraction for rendering API
            auto glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC) glXGetProcAddress(
                    (const GLubyte *) "glXSwapIntervalEXT");
            glXSwapIntervalEXT(m_display, m_windows[title].first, enabled);
        }

        void X11::setContextOfWindow(std::string_view title) {
            //TODO: Create abstraction for rendering API
            glXMakeContextCurrent(m_display, m_windows[title].first, m_windows[title].first, m_context);
        }

        void X11::updateWindows() {
            for(auto& [title, window] : m_windows) {
                if(window.second)
                    swapBuffersOfWindow(title);
            }

            poolEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }

        X11::~X11() = default;
    }
}