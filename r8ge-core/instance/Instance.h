#ifndef R8GE_INSTANCE_H
#define R8GE_INSTANCE_H

#include "../Core.h"
#include "layers/LayerSwitcher.h"

namespace r8ge {
    class Instance {
    public:
        Instance();
        virtual ~Instance();

        void eventReceiver(const std::shared_ptr<Event>& event);

        void update();

    private:
        LayerSwitcher m_layerSwitecher;
    };
}

#endif//!R8GE_INSTANCE_H
