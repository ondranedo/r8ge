//
// Created by karnatour on 4.2.24.
//

#ifndef R8GE_SCENE_H
#define R8GE_SCENE_H

#include "Entity.h"
#include "Camera.h"
#include <filesystem>

namespace r8ge {
    namespace video {

        class Scene {
        public:
            void init();

            void addEntity(Entity *entity);

            void removeEntity(unsigned long id);

            void copySelectedEntity();

            void render();

            void changeTexture(const Texture2D& texture);

            void changeMaterial(const Material& material);

            void changeTransformation(const Transformation& transform);

            void changeCamera(float deltaTime);

            void handleTreeNodeSelect(int nodeIndex);

            Camera& getCamera();

            Entity* getEntity(unsigned long id);

        private:
            Camera m_camera = Camera(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f);
            std::unordered_map<unsigned long, Entity *> m_entities;
            Entity *m_selectedEntityPtr = nullptr;
            std::vector<Program> m_shaderLibrary;
        };

    } // r8ge
} // video

#endif //R8GE_SCENESTRUCTS_H
