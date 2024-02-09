//
// Created by karnatour on 5.2.24.
//

#include "Entity.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <random>
#include "../Video.h"

namespace r8ge {
    namespace video {

        unsigned long Entity::m_nextID = 0;

        Entity::Entity(Scene &scene) : m_id(m_nextID++),m_scene(scene) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(0.5f, 1.0f);
            std::uniform_real_distribution<float> dis1(-1.0f, 1.0f);
            std::uniform_real_distribution<float> dis3(-10.0f, 10.0f);
            Video::getRenderingService()->compileProgram(m_shader);
            m_transformation.model = glm::mat4(1.0f);
            m_transformation.projection = glm::perspective(glm::radians(45.0f),
                                                           static_cast<float>(Video::getWindowingService()->getWidth()) /
                                                           static_cast<float>(Video::getWindowingService()->getHeight()), 0.1f, 100.0f);

            m_transformation.model = glm::translate(m_transformation.model,glm::vec3(dis3(gen),dis1(gen),dis1(gen)));
            m_transformation.model = glm::scale(m_transformation.model,glm::vec3(dis(gen),dis(gen),dis(gen)));

        }

        unsigned long Entity::getEntityID() const {
            return m_id;
        }

        void Entity::changeTexture(const Texture2D &texture) {
            m_texture.setData(texture);
            m_hasTexture = true;
        }

        void Entity::changeMaterial(const Material &material) {
            m_material = material;
            m_hasMaterial = true;
        }

        void Entity::changeTransformation(const Transformation &transformation) {
            m_transformation = transformation;
        }

        bool Entity::getTextureState() const {
            return m_hasTexture;
        }

        bool Entity::getMaterialState() const {
            return m_hasMaterial;
        }

        void Entity::setUpdateFunction(Entity::UpdateFunction function) {
            m_updateFunction = function;
        }

        void EntityModel::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_model.render(m_shader,m_transformation);
        }


        void EntityCube::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_cubeMesh.render(m_shader,m_transformation);
        }

        void EntitySphere::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_sphereMesh.render(m_shader,m_transformation);
        }

        void EntityCylinder::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_cylinderMesh.render(m_shader,m_transformation);
        }

    } // r8ge
} // video