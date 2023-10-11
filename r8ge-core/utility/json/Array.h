#ifndef R8GE_ARRAY_H
#define R8GE_ARRAY_H

#include <vector>

#include "Json.h"

namespace r8ge {
    class Array {
    public:
        Array();
        Array(const std::initializer_list<Json>& list);
        void add(const Json& value);
        Json& operator[](size_t index);

        [[nodiscard]] std::string to_string() const;
    private:
        std::vector<Json> m_vector;
    };
}

#endif//!R8GE_ARRAY_H
