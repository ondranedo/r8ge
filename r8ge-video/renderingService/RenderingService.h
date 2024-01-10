#ifndef R8GE_RENDERINGSERVICE_H
#define R8GE_RENDERINGSERVICE_H

#include <memory>
#include <vector>

#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "../types/Color.h"
#include "../types/Vertex.h"

#include "../r8ge-video/renderingService/openGL/GLTexture.h"
#include "programManager/Program.h"

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

            virtual void render() const = 0;

            void setClearColor(ColorRGBA c);

            virtual void setIndexBuffer(const IndexBuffer& ib) = 0;
            virtual void setVertexBuffer(const VertexBuffer& vb) = 0;

            virtual void setTexture(const GLTexture& tex) = 0;

            virtual void setProgram(const Program& program) = 0;

            virtual bool compileProgram(Program& program) = 0;
        public:
            static std::shared_ptr<RenderingService> create(API api);

        protected:
            ColorRGBA m_clearColor;
        };
    }
}

#endif//!R8GE_RENDERINGSERVICE_H
