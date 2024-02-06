//
// Created by karnatour on 5.2.24.
//

#ifndef R8GE_ENTITY_H
#define R8GE_ENTITY_H

#include "Model.h"
#include <utility>

namespace r8ge {
    namespace video {

        class Entity {
        public:
            Entity() : m_id(m_nextID++) {};

            unsigned long getEntityID();

            virtual void render() = 0;

            virtual void update(float deltaTime) = 0;

            [[nodiscard]] virtual Entity* clone() const = 0;

            void attachTexture();

            bool getMaterialState();

            bool getTextureState();

        protected:
            static unsigned long m_nextID;
            unsigned long m_id;
            bool m_hasMaterial = false;
            bool m_hasTexture = false;
            //Program m_shader;
        };

        class EntityModel : public Entity {
        public:
            void render() override;

            void update(float deltaTime) override;

            Entity* clone() const override;

            void attachModel(const std::string& path);
        private:
            Model m_model;
        };

        class EntityCube : public Entity {
        public:
            void render() override;
            void update(float deltaTime) override;

        private:
        };

        class EntitySphere : public Entity {
        public:
            void render() override;

            void update(float deltaTime) override;

        private:
        };

        class EntityCylinder : public Entity {
        public:
            void render() override;

            void update(float deltaTime) override;

        private:
        };

    } // r8ge
} // video

#endif //R8GE_ENTITY_H
