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

    private:
        std::shared_ptr<video::WindowingService> m_windowingService;
        std::mutex m_mutex;
        bool m_isRunning;
    };

    namespace global {
        extern std::unique_ptr<Video> video;
    }
}

#endif//!R8GE_VIDEO_H
