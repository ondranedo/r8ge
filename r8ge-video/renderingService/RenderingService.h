#ifndef R8GE_RENDERINGSERVICE_H
#define R8GE_RENDERINGSERVICE_H

#include <memory>

namespace r8ge {
    namespace video {
        class RenderingService {
        public:
            enum class API {
                OpenGL
            };

            RenderingService();
            virtual ~RenderingService();

            virtual void init() = 0;
            virtual void exit() = 0;
        public:
            static std::shared_ptr<RenderingService> create(API api);
        };
    }
}

#endif//!R8GE_RENDERINGSERVICE_H
