#ifndef R8GE_LAYERSWITCHER_H
#define R8GE_LAYERSWITCHER_H

#include <vector>
#include "Layers.h"

namespace r8ge {
    class LayerSwitcher final {
    public:
        LayerSwitcher();

        void pushFront(const std::shared_ptr<Layer>& l);
        void pushBack(const std::shared_ptr<Layer>& l);
        void pop(const std::string& name);
        void pop(size_t index);
        void popFront();
        void popBack();

        void sendEvent(const std::shared_ptr<Event>& e) const;
        void updateAll() const;
        void renderAll() const;

        [[nodiscard]] std::string to_string() const;
    private:
        std::vector<std::shared_ptr<Layer>> m_layers;
    };
}

#endif//!R8GE_LAYERSWITCHER_H
