//
// Created by karnatour on 25.1.24.
//

#ifndef R8GE_MESH_H
#define R8GE_MESH_H

#include "../renderingService/openGL/GLTexture.h"
#include "../types/Vertex.h"

namespace r8ge {
    namespace video {

        class Mesh {
            Mesh(std::vector <VertexColorTexture3D>& vertices, std::vector <unsigned int>& indices,
                       std::vector <GLTexture>& textures);
        };

    } // r8ge
} // video

#endif //R8GE_MESH_H
