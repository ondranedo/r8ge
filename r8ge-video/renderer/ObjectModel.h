//
// Created by karnatour on 23.1.24.
//

#ifndef R8GE_OBJECTMODEL_H
#define R8GE_OBJECTMODEL_H

#include <json.hpp>
#include <glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../renderingService/openGL/GLTexture.h"
#include "../types/Vertex.h"


using json = nlohmann::json;

namespace r8ge {
    namespace video {

        class ObjectModel {
        public:
            ObjectModel(const std::string &filePath);


        private:
            std::vector<unsigned char> getBinaryData();

            std::vector<float> getFloats(json accessor);

            std::vector<unsigned int> getIndices(json accessor);

            std::vector<GLTexture> getTextures();

            std::vector<glm::vec2> convertFloatsToVec2(const std::vector<float> &floatVector);

            std::vector<glm::vec3> convertFloatsToVec3(const std::vector<float> &floatVector);

            std::vector<glm::vec4> convertFloatsToVec4(const std::vector<float> &floatVector);

            std::vector<glm::vec3> getVec3FromAccessor(unsigned int accessorIndex);

            std::vector<glm::vec2> getVec2FromAccessor(unsigned int accessorIndex);

            void loadMesh(unsigned int meshIndex);

            void connectNode(unsigned int nodeIndex, const glm::mat4 &parentMatrix);

            glm::vec3 getVec3FromJSON(const json &node, const std::string &key, const glm::vec3 &defaultVal);

            glm::quat getQuatFromJSON(const json &node, const std::string &key, const glm::quat &defaultVal);

            glm::mat4 getMat4FromJSON(const json &node, const std::string &key, const glm::mat4 &defaultVal);

            void storeMeshTransformations(const glm::vec3 &translation, const glm::quat &rotation,
                                          const glm::vec3 &scale, const glm::mat4 &matrix);

            std::vector<VertexColorTexture3D>
            buildLayout(const std::vector<glm::vec3> &positions, const std::vector<glm::vec3> &normals,
                        const std::vector<glm::vec2> &texUVs);

            json m_glTF;
            std::string m_filePath;

            std::vector<unsigned char> m_data;
            std::vector<glm::vec3> m_translations;
            std::vector<glm::quat> m_rotations;
            std::vector<glm::vec3> m_scales;
            std::vector<glm::mat4> m_matrices;
            std::vector<ObjectModel> m_objectModels;

            std::unordered_map<std::string, Texture2D> m_loadedTextures;
        };

    } // r8ge
} // video

#endif //R8GE_OBJECTMODEL_H
