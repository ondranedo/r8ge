#ifndef R8GE_LAYERS_H
#define R8GE_LAYERS_H

#include "../../Core.h"
#include "../../events/Event.h"

#include <memory>

namespace r8ge {
    R8GE_API class Layer {
    public:
        explicit Layer(const std::string& name);
        virtual ~Layer();

        virtual void update() const = 0;
        virtual void event(const std::shared_ptr<Event>& event) const = 0;
        virtual void render() const = 0;

        [[nodiscard]] std::string getName() const;

    private:
        std::string m_name;
    };
}

#endif//!R8GE_LAYERS_H
