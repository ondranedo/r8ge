#include "LayerSwitcher.h"

#include <algorithm>
#include <sstream>
#include <ranges>

#include "../../Logger.h"

namespace r8ge {

    void LayerSwitcher::pushFront(const std::shared_ptr<Layer> &l) {
        m_layers.push_back(l);

        R8GE_LOG("Layer `{}` added to LayerSwitcher [{}]", l->getName(), to_string());
    }

    void LayerSwitcher::pushBack(const std::shared_ptr<Layer> &l) {
        pushFront(l);
        std::rotate(m_layers.rbegin(), m_layers.rbegin() + 1, m_layers.rend());
    }

    void LayerSwitcher::pop(const std::string &name) {
        R8GE_ASSERT(!m_layers.empty(), "Trying to pop() Layer `{}` from an empty LayerSwitcher", name);

        for(auto[i, l] : m_layers | std::views::enumerate)
        {
            if(l->getName()==name)
            {
                pop(i);
                return;
            }
        }
    }

    void LayerSwitcher::pop(size_t index) {
        R8GE_ASSERT(!m_layers.empty(), "Trying to pop() Layer from an empty LayerSwitcher");
        m_layers.erase(m_layers.begin()+index);
    }

    void LayerSwitcher::popFront() {
        R8GE_ASSERT(!m_layers.empty(), "Trying to popFront() Layer from an empty LayerSwitcher");
        m_layers.pop_back();
    }

    void LayerSwitcher::popBack() {
        R8GE_ASSERT(!m_layers.empty(), "Trying to popBack() Layer from an empty LayerSwitcher");
        m_layers.erase(m_layers.begin());
    }

    void LayerSwitcher::sendEvent(const std::shared_ptr<Event> &e) const {
        for(size_t i = m_layers.size()-1;i;--i)
        {
            if(!e->isHandled())
                m_layers[i]->event(e);
            else
                return;
        }
    }

    void LayerSwitcher::updateAll() const {
        for(auto& l : m_layers)
            l->update();

    }

    void LayerSwitcher::renderAll() const {
        for(auto& l : m_layers)
            l->render();
    }

    LayerSwitcher::LayerSwitcher() : m_layers{}{}

    std::string LayerSwitcher::to_string() const {
        std::stringstream ss;

        for(auto[i, l] : m_layers | std::views::enumerate)
            ss << l->getName()  << "[" << i << "]" << "<-";
        ss << "@";
        return ss.str();
    }
}