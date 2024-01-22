//
// Created by karnatour on 21.1.24.
//

#include "Gltf.h"
#include "../../Logger.h"

namespace r8ge {
    namespace reader {

        Gltf::Gltf(std::string_view path) : Text(path) {
            write("");
        }

        Gltf::~Gltf() {

        }

        utility::Json &Gltf::gltf() {
            return m_gltf;
        }

        void Gltf::load_gltf() {
            load();
            m_gltf.from_string(readFile());
            write("");
            m_materials = m_gltf["materials"];
            m_meshes = m_gltf["meshes"];
            m_accessors = m_gltf["accessors"];
            m_scenes = m_gltf["scenes"];
            m_bufferViews = m_gltf["bufferViews"];
            //m_nodes = m_gltf["nodes"];
        }

        FileType Gltf::getType() {
            return FileType::GLTF;
        }

        void Gltf::save_gltf() {
            write(m_gltf.to_string(true));
            save();
            write("");
        }

        GltfObject Gltf::parse() {
            GltfObject temp;

            for (int i = 0; i < m_materials.size(); ++i) {
                mainMaterials tempMaterials{};
                tempMaterials.materialName = m_materials[i]["name"].as_string(false);
                tempMaterials.pbrMetallicRoughness.metallicFactor = static_cast<float>(m_materials[i]["pbrMetallicRoughness"]["metallicFactor"].as_decimal());
                tempMaterials.pbrMetallicRoughness.metallicFactor = static_cast<float>(m_materials[i]["pbrMetallicRoughness"]["roughnessFactor"].as_decimal());

                for (int j = 0; j < 4; ++j) {
                    tempMaterials.pbrMetallicRoughness.baseColor[j] = static_cast<float>(m_materials[i]["pbrMetallicRoughness"]["baseColorFactor"][j].as_decimal());
                }
            }

            for (int i = 0; i < m_meshes.size(); ++i) {
                mainMeshes tempMesh{};
                tempMesh.meshName = m_meshes[i]["name"].as_string(false);
                auto primitivesArray = m_meshes[i]["primitives"];
                for (int j = 0; j < primitivesArray.size(); ++j) {
                    subPrimitives tempPrimitive{};
                    auto primitive = primitivesArray[j];

                    tempPrimitive.mode = primitive["mode"].as_integral();
                    tempPrimitive.materialIndex = primitive["material"].as_integral();
                    tempPrimitive.indicesIndex = primitive["indices"].as_integral();

                    tempPrimitive.attributes.position = primitive["attributes"]["POSITION"].as_integral();
                    tempPrimitive.attributes.normal = primitive["attributes"]["NORMAL"].as_integral();
                    tempPrimitive.attributes.tangent = primitive["attributes"]["TANGENT"].as_integral();

                    tempMesh.primitives.push_back(tempPrimitive);

                }
                gltfObject.meshList.push_back(tempMesh);

            }

            for (int i = 0; i < m_accessors.size(); ++i) {
                mainAccessors tempAccessor{};
                tempAccessor.bufferOffest = m_accessors[i]["bufferOffset"].as_integral();
                tempAccessor.bufferView = m_accessors[i]["bufferView"].as_integral();
                tempAccessor.componentType = static_cast<int>(m_accessors[i]["componentType"].as_integral());
                tempAccessor.type = m_accessors[i]["type"].as_string(false);
                tempAccessor.count = m_accessors[i]["count"].as_integral();

                for (int j = 0; j < 3; ++j) {
                    tempAccessor.min[j] = static_cast<float>(m_accessors[i]["min"][j].as_decimal());
                    tempAccessor.max[j] = static_cast<float>(m_accessors[i]["max"][j].as_decimal());
                }

                gltfObject.accessorList.push_back(tempAccessor);
            }

            for (int i = 0; i < m_scenes.size(); ++i) {
                mainScenes tempScene{};
                tempScene.sceneName = m_scenes[i]["name"].as_string(false);
                tempScene.nodeIndices[0] = static_cast<int>(m_scenes[i]["nodes"][0].as_integral());

                gltfObject.sceneList.push_back(tempScene);
            }

            for (int i = 0; i < m_bufferViews.size(); ++i) {
                mainBufferViews tempBufferView{};
                tempBufferView.bufferIndex = m_bufferViews[i]["buffer"].as_integral();
                tempBufferView.byteLength = m_bufferViews[i]["byteLength"].as_integral();
                tempBufferView.byteOffset = m_bufferViews[i]["byteOffset"].as_integral();
                tempBufferView.byteStride = m_bufferViews[i]["byteStride"].as_integral();
                tempBufferView.target = m_bufferViews[i]["target"].as_integral();

                gltfObject.bufferViewList.push_back(tempBufferView);
            }

            for (int i = 0; i < m_nodes.size(); ++i) {
                mainNodes tempNodes{};
                tempNodes.meshIndex = static_cast<int>(m_nodes[i]["mesh"].as_integral());
                tempNodes.children[0] = static_cast<float>(m_nodes[i]["children"][0].as_decimal());
                for (int j = 0; j < 16; ++j) {
                    tempNodes.matrix[j] = static_cast<float>(m_nodes[i]["matrix"][j].as_decimal());
                }
                gltfObject.nodeList.push_back(tempNodes);
            }
            return temp;
        }


    }

} // r8ge
// reader