#ifndef R8GE_VIDEO_H
#define R8GE_VIDEO_H

#include "platform/WindowingService.h"
#include <memory>

namespace r8ge {
    class Video {
    public:
        Video();
        ~Video();

        void init();
        void run();
        void exit();

    public:
        std::string m_title;

    private:


    public:
        static std::shared_ptr<video::WindowingService> getWindowingService();

    private:
        static std::shared_ptr<video::WindowingService> s_windowingService;
        static bool s_isReady;
    };
}

#endif//!R8GE_VIDEO_H
