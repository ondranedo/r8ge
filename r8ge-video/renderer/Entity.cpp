//
// Created by karnatour on 5.2.24.
//

#include "Entity.h"

namespace r8ge {
    namespace video {

        unsigned long Entity::m_nextID = 0;

        unsigned long Entity::getEntityID() {
            return m_id;
        }

        void EntityModel::render() {
            //m_model.render();
        }

        void EntityModel::update(float deltaTime) {

        }

        void EntityModel::attachModel(const std::string& path) {
            Model temp(path);
            m_model = temp;
        }

        Entity *EntityModel::clone() const {
            return new EntityModel(*this);
        }

    } // r8ge
} // video