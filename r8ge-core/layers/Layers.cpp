#include "Layers.h"

namespace r8ge {
    Layer::Layer(const std::string &name) : m_name() {}

    Layer::~Layer() = default;

    std::string Layer::getName() const {
        return m_name;
    }

}
