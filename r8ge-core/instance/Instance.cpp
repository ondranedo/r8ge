#include "Instance.h"

namespace r8ge {
    Instance::Instance() : m_layerSwitecher() {}

    void Instance::eventReceiver(const std::shared_ptr<Event>& event)
    {
        m_layerSwitecher.sendEvent(event);
    }

    void Instance::update() {
        m_layerSwitecher.updateAll();
        m_layerSwitecher.renderAll();
    }
}