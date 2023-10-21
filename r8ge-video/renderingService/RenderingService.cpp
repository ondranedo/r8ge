#include "RenderingService.h"

#include "openGL/GLService.h"

#include <memory>

namespace r8ge {
    namespace video {
        RenderingService::RenderingService() = default;
        RenderingService::~RenderingService() = default;

        std::shared_ptr<RenderingService> RenderingService::create(RenderingService::API api) {
            switch (api) {
                case RenderingService::API::OpenGL:  return std::make_shared<GLService>();
                default: return nullptr;
            }
        }
    }
}