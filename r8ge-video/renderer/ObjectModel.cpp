//
// Created by karnatour on 23.1.24.
//

#include "ObjectModel.h"
#include "Mesh.h"
#include "Mesh.h"


#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        ObjectModel::ObjectModel(const std::string &filePath) {
            File<reader::Text> file(filePath);
            std::string text = file->readFile();
            m_glTF = json::parse(text);

            m_filePath = filePath;
            m_data = getBinaryData();
        }

        void ObjectModel::loadMesh(unsigned int meshIndex) {
            auto &meshData = m_glTF["meshes"][meshIndex]["primitives"][0];
            unsigned int posAccInd = meshData["attributes"]["POSITION"];
            unsigned int normalAccInd = meshData["attributes"]["NORMAL"];
            unsigned int texAccInd = meshData["attributes"]["TEXCOORD_0"];
            unsigned int indAccInd = meshData["indices"];

            std::vector<glm::vec3> positions = getVec3FromAccessor(posAccInd);
            std::vector<glm::vec3> normals = getVec3FromAccessor(normalAccInd);
            std::vector<glm::vec2> texUVs = getVec2FromAccessor(texAccInd);

            std::vector<VertexColorTexture3D> vertices = buildLayout(positions, normals, texUVs);
            std::vector<unsigned int> indices = getIndices(indAccInd);

            std::vector<GLTexture> textures = getTextures();

            m_objectModels.push_back(Mesh(vertices, indices, textures));
        }

        std::vector<VertexColorTexture3D> ObjectModel::buildLayout(const std::vector<glm::vec3> &positions,
                                                                   const std::vector<glm::vec3> &normals,
                                                                   const std::vector<glm::vec2> &texUVs) {
            std::vector<VertexColorTexture3D> vertices;
            vertices.reserve(positions.size());

            for (size_t i = 0; i < positions.size(); ++i) {
                vertices.emplace_back(positions[i].x, positions[i].y, positions[i].z,
                                      ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f),
                                      texUVs[i].x, texUVs[i].y,
                                      normals[i].x, normals[i].y, normals[i].z);
            }

            return vertices;

        }


        std::vector<glm::vec3> ObjectModel::getVec3FromAccessor(unsigned int accessorIndex) {
            std::vector<float> data = getFloats(m_glTF["accessors"][accessorIndex]);
            return convertFloatsToVec3(data);
        }

        std::vector<glm::vec2> ObjectModel::getVec2FromAccessor(unsigned int accessorIndex) {
            std::vector<float> data = getFloats(m_glTF["accessors"][accessorIndex]);
            return convertFloatsToVec2(data);
        }

        std::vector<unsigned char> ObjectModel::getBinaryData() {
            std::string binaryContent;
            std::string uri = m_glTF["buffers"][0]["uri"];

            std::string fileDirectory = m_filePath.substr(0, m_filePath.find_last_of('/') + 1);
            File<reader::Text> file(fileDirectory + uri);
            binaryContent = file->readFile();

            std::vector<unsigned char> data(binaryContent.begin(), binaryContent.end());
            return data;
        }

        std::vector<float> ObjectModel::getFloats(json accessor) {
            std::vector<float> floatVector;

            unsigned int buffViewInd = accessor.value("bufferView", 1);
            unsigned int count = accessor["count"];
            unsigned int accByteOffset = accessor.value("byteOffset", 0);
            std::string type = accessor["type"];

            json bufferView = m_glTF["bufferViews"][buffViewInd];
            unsigned int byteOffset = bufferView["byteOffset"];

            unsigned int numPerVert;
            if (type == "SCALAR") {
                numPerVert = 1;
            }
            else if (type == "VEC2") {
                numPerVert = 2;
            }
            else if (type == "VEC3") {
                numPerVert = 3;
            }
            else if (type == "VEC4") {
                numPerVert = 4;
            }
            else {
                R8GE_LOG_ERROR("Invalid type in GLTF accessor");
            }

            unsigned int beginningOfData = byteOffset + accByteOffset;
            unsigned int lengthOfData = count * 4 * numPerVert;

            for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i += 4) {
                float temp;
                std::memcpy(&temp, &m_data[i], sizeof(float));
                floatVector.push_back(temp);
            }

            return floatVector;
        }

        std::vector<unsigned int> ObjectModel::getIndices(json accessor) {
            std::vector<unsigned int> indices;

            unsigned int buffViewInd = accessor.value("bufferView", 0);
            unsigned int count = accessor["count"];
            unsigned int accByteOffset = accessor.value("byteOffset", 0);
            unsigned int componentType = accessor["componentType"];

            const auto &bufferView = m_glTF["bufferViews"][buffViewInd];
            unsigned int byteOffset = bufferView["byteOffset"];

            unsigned int beginningOfData = byteOffset + accByteOffset;

            for (unsigned int i = beginningOfData; i < beginningOfData + count * 2; i += 2) {
                unsigned char bytes[] = {m_data[i], m_data[i + 1]};

                if (componentType == 5125) {
                    indices.push_back(*reinterpret_cast<unsigned int *>(bytes));
                }
                else if (componentType == 5123) {
                    indices.push_back(*reinterpret_cast<unsigned short *>(bytes));
                }
                else if (componentType == 5122) {
                    indices.push_back(*reinterpret_cast<short *>(bytes));
                }
            }

            return indices;
        }


        std::vector<GLTexture> ObjectModel::getTextures() {
            std::vector<GLTexture> textures;

            std::string fileDirectory = m_filePath.substr(0, m_filePath.find_last_of('/') + 1);

            for (const auto &image: m_glTF["images"]) {

                std::string texPath = image["uri"];

                auto it = m_loadedTextures.find(texPath);
                if (it != m_loadedTextures.end()) {
                    textures.emplace_back(it->second);
                }
                else {
                    if (texPath.find("baseColor") != std::string::npos) {
                        Texture2D diffuse(fileDirectory + texPath, false);
                        textures.emplace_back(diffuse);
                        m_loadedTextures.emplace(texPath, diffuse);
                    }

                    else if (texPath.find("metallicRoughness") != std::string::npos) {
                        Texture2D specular(fileDirectory + texPath, false);
                        textures.emplace_back(specular);
                        m_loadedTextures.emplace(texPath, specular);
                    }
                }
            }
            return textures;
        }

        std::vector<glm::vec2> ObjectModel::convertFloatsToVec2(const std::vector<float> &floatVector) {
            std::vector<glm::vec2> vectors;
            for (int i = 0; i < floatVector.size(); i += 2) {
                vectors.emplace_back(floatVector[i], floatVector[i + 1]);
            }
            return vectors;
        }

        std::vector<glm::vec3> ObjectModel::convertFloatsToVec3(const std::vector<float> &floatVector) {
            std::vector<glm::vec3> vectors;
            for (int i = 0; i < floatVector.size(); i += 3) {
                vectors.emplace_back(floatVector[i], floatVector[i + 1], floatVector[i + 2]);
            }
            return vectors;
        }

        std::vector<glm::vec4> ObjectModel::convertFloatsToVec4(const std::vector<float> &floatVector) {
            std::vector<glm::vec4> vectors;
            for (int i = 0; i < floatVector.size(); i += 4) {
                vectors.emplace_back(floatVector[i], floatVector[i + 1], floatVector[i + 2], floatVector[i + 3]);
            }
            return vectors;
        }

        void ObjectModel::connectNode(unsigned int nodeIndex, const glm::mat4 &parentMatrix) {
            json currentNode = m_glTF["nodes"][nodeIndex];

            glm::vec3 translation = getVec3FromJSON(currentNode, "translation", glm::vec3(0.0f));
            glm::quat rotation = getQuatFromJSON(currentNode, "rotation", glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
            glm::vec3 scale = getVec3FromJSON(currentNode, "scale", glm::vec3(1.0f));
            glm::mat4 nodeMatrix = getMat4FromJSON(currentNode, "matrix", glm::mat4(1.0f));

            glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 rotMatrix = glm::mat4_cast(rotation);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

            glm::mat4 matNextNode = parentMatrix * nodeMatrix * transMatrix * rotMatrix * scaleMatrix;

            if (currentNode.find("mesh") != currentNode.end()) {
                storeMeshTransformations(translation, rotation, scale, matNextNode);
                loadMesh(currentNode["mesh"]);
            }

            if (currentNode.find("children") != currentNode.end()) {
                for (const auto &i: currentNode["children"])
                    connectNode(i, matNextNode);
            }
        }

        glm::vec3 ObjectModel::getVec3FromJSON(const json &node, const std::string &key, const glm::vec3 &defaultVal) {
            glm::vec3 result = defaultVal;
            if (node.find(key) != node.end()) {
                for (unsigned int i = 0; i < node[key].size(); i++)
                    result[i] = node[key][i];
            }
            return result;
        }

        glm::quat ObjectModel::getQuatFromJSON(const json &node, const std::string &key, const glm::quat &defaultVal) {
            glm::quat result = defaultVal;
            if (node.find(key) != node.end()) {
                for (unsigned int i = 0; i < node[key].size(); i++)
                    result[i] = node[key][i];
            }
            return result;
        }

        glm::mat4 ObjectModel::getMat4FromJSON(const json &node, const std::string &key, const glm::mat4 &defaultVal) {
            glm::mat4 result = defaultVal;
            if (node.find(key) != node.end() && node[key].size() == 16) {
                for (unsigned int i = 0; i < 4; ++i) {
                    for (unsigned int j = 0; j < 4; ++j) {
                        result[i][j] = node[key][i * 4 + j];
                    }
                }
            }
            return result;
        }


        void ObjectModel::storeMeshTransformations(const glm::vec3 &translation, const glm::quat &rotation,
                                                   const glm::vec3 &scale, const glm::mat4 &matrix) {
            m_translations.push_back(translation);
            m_rotations.push_back(rotation);
            m_scales.push_back(scale);
            m_matrices.push_back(matrix);
        }

    } // r8ge
} // video