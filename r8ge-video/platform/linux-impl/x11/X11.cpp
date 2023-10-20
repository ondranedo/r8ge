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
                //|   SubstructureNotifyMask
                //|   StructureNotifyMask
                //|   SubstructureRedirectMask
                ;
            //m_windowAttributes.do_not_propagate_mask = 0; // Do not propagate any events

            XColor magenta = {0xFF, 0x00, 0xFF};
            m_windowAttributes.background_pixel = magenta.pixel;

            R8GE_LOG("X11 windowing service initialized");

            //  TODO: Create context for rendering API
            m_context = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);
            R8GE_ASSERT(m_context, "X11 Context failed to create");
            R8GE_LOG("X11 gl Context created");
        }

        void X11::release() {
            for(auto& [title, window] : m_windows) {
                    destroyWindow(title);
                if(window.second)
                R8GE_LOG_WARNI("X11 Window `{}` was not destroyed, destroying it now", title);
            }
            R8GE_LOG("X11 windowing service released");
        }

        bool X11::createWindow(size_t width, size_t height, std::string_view title) {
            R8GE_LOG("Creating X11 Window `{}`", title);

            if(m_windows.size()>1)
            {
                R8GE_LOG_WARNI("X11 R8GE-VIDEO only supports 1 window");
                return false;
            }

            if(isWindowPresent(title))
            {
                R8GE_LOG_WARNI("X11 Window `{}` already exists", title);
                return false;
            }


            ::Window win = XCreateWindow(
                    m_display, m_rootWindow,
                    0, 0,
                    width, height,
                    0,
                    m_visual->depth, InputOutput, m_visual->visual,
                    CWColormap | CWEventMask,
                    &m_windowAttributes);

            if(!win)
            {
                R8GE_LOG_ERROR("X11 Window `{}` failed to create", title);
                return false;
            }

            XStoreName(m_display, win, title.data());

            bool wasEmpty = m_windows.empty();

            // TODO: Move to RenderingAPI
            m_windows[title] = {win, false};
            setContextOfWindow(title);

            // TODO: Move to RenderingAPI
            if(wasEmpty) {
                auto res = glewInit();
                R8GE_ASSERT(res == GLEW_OK, "Failed to initialize GLEW: `{}`", (char *) glewGetErrorString(res));
            }


            R8GE_LOG_INFOR("X11 Window `{}` created", title.data());

            m_windowCount++;
            m_windows[title].second =  true;
            return true;
        }

        bool X11::showWindow(std::string_view title) {
            if(!isWindowPresent(title))
            {
                R8GE_LOG_WARNI("X11 Window `{}` can't be found when showing it", title);
                return false;
            }

            XMapWindow(m_display, m_windows[title].first);
            return true;
        }

        bool X11::hideWindow(std::string_view title) {
            if(!isWindowPresent(title))
            {
                R8GE_LOG_WARNI("X11 Window `{}` can't be found when hiding it", title);
                return false;
            }

            return false;
        }

        bool X11::destroyWindow(std::string_view title) {
            if(!isWindowPresent(title)) {
                R8GE_LOG_WARNI("X11 Window `{}` can't be found when destroying it", title);
                return false;
            }
            XDestroyWindow(m_display, m_windows[title].first);
            m_windows.erase(title);
            m_windowCount--;
            return true;
        }

        X11::X11() : m_display(nullptr), m_rootWindow(0), m_visual(nullptr), m_colormap(0), m_windowAttributes{} {}

        void X11::poolEvents() {
            XEvent event;
            while (XPending(m_display) > 0) {
                XNextEvent(m_display, &event);

                switch (event.type) {
                    case Expose:
                        break;
                    case KeyPress:
                        break;
                    case KeyRelease:
                        break;
                    default:
                        break;
                }
            }
        }

        void X11::swapBuffersOfWindow(std::string_view title) {
            if(!isWindowPresent(title))
            {
                R8GE_LOG_WARNI("X11 Window `{}` can't be found when swapping buffers", title);
                return;
            }

            //TODO: Add double buffering option into settings,
            //      Create abstraction for rendering API
            glXSwapBuffers(m_display, m_windows[title].first);
        }

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
        }

        void X11::setContextOfWindow(std::string_view title) {
            if(!isWindowPresent(title))
            {
                R8GE_LOG_WARNI("X11 Window `{}` can't be found when setting context to current", title);
                return;
            }

            //TODO: Create abstraction for rendering API
            glXMakeCurrent(m_display, m_windows[title].first, m_context);
            //glXMakeContextCurrent(m_display, m_windows[title].first, m_windows[title].first, m_context);
        }

        void X11::updateWindows() {
            for(auto& [title, window] : m_windows) {
                if(window.second) { // Is created
                    setContextOfWindow(title);
                    swapBuffersOfWindow(title);
                }
            }

            poolEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }

        X11::~X11() = default;

        bool X11::isWindowPresent(std::string_view title) const {
            if(!m_windows.contains(title))
                return false;
            return true;
        }
    }
}