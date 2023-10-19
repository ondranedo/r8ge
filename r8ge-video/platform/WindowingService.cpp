#include "WindowingService.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        WindowingService::WindowingService() : m_windowCount(0) {}
        WindowingService::~WindowingService() = default;

        std::shared_ptr<WindowingService> WindowingService::s_activeService = nullptr;

        WindowingService &WindowingService::getService() {
            if(!s_activeService) {
                R8GE_LOG_FATAL("No active windowing service, internal error in r8ge-video");
            }
            return *s_activeService;
        }

        void WindowingService::releaseService() {
            if(s_activeService)
                s_activeService = nullptr;
        }

        void WindowingService::setActiveService(const std::shared_ptr<WindowingService>& service) {
            if(s_activeService) {
                R8GE_LOG_WARNI("Windowing service already active, releasing previous service");
            }
            s_activeService = service;
        }
    }
}