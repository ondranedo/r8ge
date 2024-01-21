//
// Created by karnatour on 21.1.24.
//

#ifndef R8GE_GLTF_H
#define R8GE_GLTF_H

#include "Text.h"
#include "../../utility/json/Json.h"

namespace r8ge {
    namespace reader {
        //https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.pdf
        struct mainMaterials {                              //materials
            std::string materialName;                       //name
            struct PbrMetallicRoughness {                   //pbrMetallicRoughness
                float baseColor[4];                         //baseColorFactor
                float metallicFactor;                       //metallicFactor
                float roughnessFactor;                      //roughnessFactor
            } pbrMetallicRoughness;
        };


        struct subPrimitives {                              //primitives
            unsigned int mode;                              //mode
            unsigned int materialIndex;                     //material
            unsigned int indicesIndex;                      //indices
            struct subPrimitivesAttributes {                //attributes
                float position;                             //POSITION
                float normal;                               //NORMAL
                float tangent;                              //TANGENT
            } attributes;
        };
        struct mainMeshes {                                 //meshes
            std::string meshName;                           //name
            std::vector<subPrimitives> primitives;          //primitives

        };


        struct mainAccessors {                              //accessors
            int componentType;                              //componentType
            unsigned int count;                             //count
            std::string type;                               //type enum->"SCALAR","VEC2","VEC3","VEC4","MAT2","MAT3","MAT4"
            std::vector<float> min;                         //min
            std::vector<float> max;                         //max
            unsigned int bufferOffest;                      //bufferOffset
            unsigned int bufferView;                        //bufferView
        };

        struct mainNodes {                                  //nodes
            float matrix[16];                               //matrix
            float children[1];                              //children
            int meshIndex;                                  //mesh
        };

        struct mainScenes{                                  //scene
            int nodeIndices[1];                             //nodes
            std::string sceneName;                          //name
        };

        struct mainBufferViews{                             //bufferViews
            unsigned int bufferIndex;                       //buffer
            unsigned int byteOffset;                        //byteOffset
            unsigned int byteLength;                        //byteLength
            unsigned int byteStride;                        //byteStride
            unsigned int target;                            //target
        };

        struct GltfObject {
            std::vector<mainMaterials> materialList;
            std::vector<mainMeshes> meshList;
            std::vector<mainAccessors> accessorList;
            std::vector<mainScenes> sceneList;
            std::vector<mainBufferViews> bufferViewList;
        };


        class Gltf : protected Text {
        public:
            GltfObject gltfObject;

            Gltf(std::string_view path);

            ~Gltf() override;

            utility::Json &gltf();

            void load_gltf();

            void save_gltf();

            static FileType getType();

            std::vector<GltfObject> parse();

        private:
            utility::Json m_gltf;
            utility::Json m_materials, m_meshes;
        };

    } // r8ge
} // reader

#endif //R8GE_GLTF_H
