#ifndef R8GE_ARRAY_H
#define R8GE_ARRAY_H

#include <vector>

#include "Json.h"

namespace r8ge {
    namespace utility {
        class Array {
        public:
            Array();
            Array(const std::initializer_list<Json>& list);
            void add(const Json& value);
            Json& operator[](size_t index);

            [[nodiscard]] std::string to_string(bool format, size_t _tab_spaces, size_t _count_of_indent = 0) const;
            size_t from_string(std::string_view str, size_t _index = 0);
            [[nodiscard]] std::vector<Json> as_vector() const;

            [[nodiscard]] size_t size() const;
        private:
            std::vector<Json> m_vector;
        };
    }
}

#endif//!R8GE_ARRAY_H
