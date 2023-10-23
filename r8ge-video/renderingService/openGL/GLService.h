#ifndef R8GE_GLSERVICE_H
#define R8GE_GLSERVICE_H

#include "../RenderingService.h"
#include "../buffers/IndexBuffer.h"

#include <vector>

#include <r8ge/r8ge.h>
#include <GL/glew.h>

namespace r8ge {
    namespace video {
        class GLService : public RenderingService {
        public:
            GLService();
            ~GLService() override;

            void init() override;
            void exit() override;

            void clear() const override;

            void render() const override;

            void setIndexBuffer(const IndexBuffer &ib) override;

            void setVertexBuffer(const VertexBuffer &vb) override;

            void setDataLayout() const;

        private:
            GLuint m_indexBuffer, m_vertexArrayObject, m_vertexBuffer;
            size_t m_indexCount;
            VertexBufferLayout m_layout;
        };
    }
}

#endif//!R8GE_GLSERVICE_H
