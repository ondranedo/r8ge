//
// Created by karnatour on 25.1.24.
//

#include "Mesh.h"

namespace r8ge {
    namespace video {
        Mesh::Mesh(std::vector<VertexColorTexture3D> &vertices, std::vector<unsigned int> &indices,
                   std::vector<GLTexture> &textures) {
            m_vertices = vertices;
            m_indices = indices;
            m_textures = textures;
            m_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);
            setupRender();
        }

        void Mesh::render(Program &shader) {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            for (unsigned int i = 0; i < m_textures.size(); ++i) {
                std::string type = m_textures[i].getType();
                std::string number;
                if (type == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if (type == "texture_specular")
                    number = std::to_string(specularNr++);
                else if (type == "texture_normal")
                    number = std::to_string(normalNr++);
                else if (type == "texture_height")
                    number = std::to_string(heightNr++);

                m_renderingService->setUniformInt(shader, type + number, static_cast<int>(i));
                m_textures[i].bindTexture(i);
            }
            m_renderingService->render(m_indices.size());
        }

        void Mesh::setupRender() {
            video::VertexBuffer vb(m_vertices, m_vertices[0].getLayout());
            video::IndexBuffer ib(m_indices);

            m_renderingService->setVertexBuffer(vb);
            m_renderingService->setIndexBuffer(ib);
            m_renderingService->preRender();
        }
    } // r8ge
} // video