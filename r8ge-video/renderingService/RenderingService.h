#ifndef R8GE_RENDERINGSERVICE_H
#define R8GE_RENDERINGSERVICE_H

#include <memory>

#include "../renderer/Color.h"

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

            virtual void clear() const = 0;

            void setClearColor(Color c);
        public:
            static std::shared_ptr<RenderingService> create(API api);

        protected:
            Color m_clearColor;
        };
    }
}

#endif//!R8GE_RENDERINGSERVICE_H
