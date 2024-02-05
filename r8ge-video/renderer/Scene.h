//
// Created by karnatour on 4.2.24.
//

#ifndef R8GE_SCENE_H
#define R8GE_SCENE_H

#include "Model.h"
#include "Entity.h"
#include "Camera.h"

namespace r8ge {
    namespace video {

        struct Transformation {
            glm::vec3 translation;
            glm::vec3 rotation;
            glm::vec3 scale;
        };

        struct Material{
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float shine;
        };

        struct ShaderLibrary{
            std::string name;
            Program shader;
        };

        class Scene {
        public:

            void init();

            void addEntity(Entity *entity);

            void removeEntity(unsigned long id);

            void copySelectedEntity();

            void changeTexture(Texture2D texture);

            void changeMaterial(Material material);

            void changeTransformation(Transformation transform);

            void handleTreeNodeSelect(int nodeIndex);

            Entity* getEntity(unsigned long id);

        private:
            std::unordered_map<unsigned long, Entity*> m_entities;
            Entity *m_selectedEntityPtr = nullptr;
            Camera m_camera;
            std::vector<ShaderLibrary> m_ShaderLibrary;
        };

    } // r8ge
} // video

#endif //R8GE_SCENE_H
