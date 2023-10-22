#ifndef R8GE_RENDERINGSERVICE_H
#define R8GE_RENDERINGSERVICE_H

#include <memory>
#include <vector>

#include "../renderer/Types.h"
#include "Vertex.h"

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

            virtual void render(const std::vector<size_t>& index_data, const std::vector<float>& vertex_data) const = 0;

            void setClearColor(Color32 c);
        public:
            static std::shared_ptr<RenderingService> create(API api);

        protected:
            Color32 m_clearColor;
        };
    }
}

#endif//!R8GE_RENDERINGSERVICE_H
