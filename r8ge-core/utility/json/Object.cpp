#include "Object.h"

namespace r8ge {
    void Object::add(const StringKey &key, const Json &value) {
        if(m_map.find(key.get()) != m_map.end())
            return;

        m_map.emplace(key.get(), value);
    }

    Object::Object(const StringKey &key, const Json &value) {
        add(key, value);
    }

    Object::Object(const std::initializer_list<std::pair<StringKey, Json>> &list) {
        for(auto& pair : list)
            add(pair.first, pair.second);
    }


    std::string Object::to_string() const {
        std::string str = "{";
        size_t i = 0;
        for(auto&[key, value]: m_map) {
            str += "\"" + key + "\":" + value.to_string();
            if(i++ < m_map.size()-1)
                str += ",";
        }
        return str + "}";
    }

    Object::Object() {
        m_map = {};
    }

    Json &Object::operator[](const StringKey &key) {
        return m_map[key.get()];
    }
}