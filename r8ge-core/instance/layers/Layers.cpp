#include "Layers.h"

#include "../../Logger.h"

namespace r8ge {
    Layer::Layer(const std::string &name) : m_name(name) {
        R8GE_LOG("Layer `{}` created", name);
    }

    Layer::~Layer() {
        R8GE_LOG("Layer `{}` destroyed", m_name);
    }
    std::string Layer::getName() const {
        return m_name;
    }

}
