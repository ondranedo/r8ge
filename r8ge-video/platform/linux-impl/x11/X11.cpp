#include "X11.h"
#include "../../WindowingService.h"


#include <r8ge/r8ge.h>


#include <GL/glx.h>


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
            m_visual = visualInfo->visual;

            R8GE_ASSERT(visualInfo, "Failed to create X11 visual");

            m_colormap = XCreateColormap(m_display,m_rootWindow, m_visual, AllocNone);
            m_windowAttributes.colormap = m_colormap;
            m_windowAttributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;

            R8GE_LOG("X11 windowing service initialized");
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
                    m_depth, InputOutput, m_visual,
                    CWColormap | CWEventMask,
                    &m_windowAttributes);

            XStoreName(m_display, win, title.data());

            if(!win)
            {
                R8GE_LOG_ERROR("Failed to create X11 window");
                return false;
            }

            m_windows[title] = win;
            m_windowCount++;

            return true;
        }

        bool X11::showWindow(std::string_view title) {
            if(!m_windows.contains(title))
            {
                R8GE_LOG_ERROR("Failed to show X11 window: window not found");
                return false;
            }

            XMapWindow(m_display, m_windows[title]);
            return true;
        }

        bool X11::hideWindow(std::string_view title) {
            return false;
        }

        bool X11::destroyWindow(std::string_view title) {
            return false;
        }

        X11::X11() : m_display(nullptr), m_rootWindow(0), m_visual(nullptr), m_colormap(0), m_depth(0), m_windowAttributes{} {}

        X11::~X11() = default;
    }
}