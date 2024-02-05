//
// Created by karnatour on 4.2.24.
//

#include "Scene.h"

namespace r8ge {
    namespace video {
        void Scene::addEntity(Entity *entity) {
            m_entities[entity->getEntityID()] = entity;
        }

        void Scene::removeEntity(unsigned long id) {
            m_entities.erase(id);
        }

        void Scene::changeTexture(Texture2D texture) {
            if (m_selectedEntityPtr) {

            }
        }

        void Scene::changeMaterial(Material material) {
            if (m_selectedEntityPtr) {

            }
        }

        void Scene::changeTransformation(Transformation transform) {
            if (m_selectedEntityPtr) {

            }
        }

        void Scene::handleTreeNodeSelect(int nodeIndex) {
            if (nodeIndex > 0 && nodeIndex < m_entities.size()) {
                m_selectedEntityPtr = m_entities[nodeIndex];
            }
            else {
                m_selectedEntityPtr = nullptr;
            }
        }

        Entity *Scene::getEntity(unsigned long id) {
            auto it = m_entities.find(id);
            if (it != nullptr) {
                return it->second;
            }
            else {
                R8GE_LOG_WARNI("Returned entity is nullptr");
                return nullptr;
            }

        }

        void Scene::init() {

        }

        void Scene::copySelectedEntity() {
            if (m_selectedEntityPtr) {
                Entity *copiedEntity = m_selectedEntityPtr;
                addEntity(copiedEntity);
            }
        }

    } // r8ge
} // video