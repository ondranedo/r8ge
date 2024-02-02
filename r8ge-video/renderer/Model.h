//
// Created by karnatour on 28.1.24.
//

#ifndef R8GE_MODEL_H
#define R8GE_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../renderingService/openGL/GLTexture.h"

namespace r8ge {
    namespace video {

        class Model {
        public:
            Model(std::string const &path);

        private:
            void connectNodes(aiNode *node, const aiScene *scene);

            void processMesh(aiMesh *mesh, const aiScene *scene);

            std::vector<GLTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                        const std::string &typeName);

            std::string m_directory;
        };

    } // r8ge
} // video

#endif //R8GE_MODEL_H
