#ifndef R8GE_INSTANCE_H
#define R8GE_INSTANCE_H

#include "../Core.h"
#include "layers/LayerSwitcher.h"

namespace r8ge {
    // The main game instance, handles the layers, and the logic,
    // does not handle the main loop, or the event queue, or the window
    // This class should be registered to the Ar8ge class
    class Instance {
    public:
        Instance();
        virtual ~Instance();

        // Called when an event is sent to the instance, this function
        // should handle the event to layer switcher
        void eventReceiver(const std::shared_ptr<Event>& event);

        // Called every frame, this function should handle the update to layer switcher
        // and the logic, and the rendering
        void update();

    private:
        LayerSwitcher m_layerSwitecher;
    };
}

#endif//!R8GE_INSTANCE_H
