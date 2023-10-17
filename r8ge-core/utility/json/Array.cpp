#include "Array.h"

namespace r8ge {
    namespace utility {
        Array::Array(const std::initializer_list<Json> &list) {
            for (auto &v: list) {
                m_vector.push_back(v);
            }
        }

        std::string Array::to_string(bool format, size_t _tab_spaces, size_t _count_of_indent) const {
            std::string str = "[";
            str += format ? "\n" : "";

            size_t i = 0;
            for (auto &v: m_vector) {
                str += v.to_string(format, _tab_spaces, _count_of_indent);
                if (i++ < m_vector.size() - 1)str += ",";
                str += format ? "\n" : "";
            }

            for (size_t c = 0; c < (_count_of_indent-1) * _tab_spaces ; c++)
                str += format ? " " : "";

            str += "]";
            return str;
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

        Json generateEntry(std::string_view str, size_t& index, size_t& bracket_count)
        {
            if(str[index] == ',') index++;

            Json j;
            index = j.from_string(str, index);

            return j;
        }

        size_t Array::from_string(std::string_view str, size_t _index) {
            size_t i = _index + 1;    // 1 for '['
            size_t bracket_count = 1; // 1 for '['

            while(bracket_count) {
                m_vector.push_back(generateEntry(str, i, bracket_count));
                if(str[i] == ']') bracket_count--;
            }

            return i + 1;  // 1 for ']'
        }
    }
}