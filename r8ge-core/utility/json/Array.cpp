#include "Array.h"

namespace r8ge {
    namespace utility {
        Array::Array(const std::initializer_list<Json> &list) {
            for (auto &v: list) {
                m_vector.push_back(v);
            }
        }

        std::string Array::to_string() const {
            std::string retstr = "[";
            size_t i = 0;
            for (auto &v: m_vector) {
                retstr += v.to_string();
                if (i++ < m_vector.size() - 1)retstr += ",";
            }

            retstr += "]";
            return retstr;
        }

        void Array::add(const Json &value) {
            m_vector.push_back(value);
        }

        Array::Array() : m_vector() {}

        Json &Array::operator[](size_t index) {
            if (index >= m_vector.size())
                index = m_vector.size() - 1;
            return m_vector[index];
        }
    }
}