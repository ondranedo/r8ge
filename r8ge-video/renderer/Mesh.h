#ifndef R8GE_MESH_H
#define R8GE_MESH_H

#include "../renderingService/openGL/GLTexture.h"
#include "../types/Vertex.h"
#include "../renderingService/RenderingService.h"

namespace r8ge {
    namespace video {

        class Mesh {
        public:
            Mesh(std::vector<VertexColorTexture3D> &vertices, std::vector<unsigned int> &indices,
                 std::vector<GLTexture> &textures);

            void render(Program &shader);
        private:
            void setupRender();

            std::vector<VertexColorTexture3D> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<GLTexture> m_textures;
            std::shared_ptr<video::RenderingService> m_renderingService;
        };

    } // r8ge
} // video

#endif //R8GE_MESH_H
