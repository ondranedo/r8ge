#ifndef R8GE_OBJECT_H
#define R8GE_OBJECT_H

#include "Json.h"
#include "StringKey.h"

#include <unordered_map>

namespace r8ge {
    namespace utility {
        class Object {
        public:
            Object();
            Object(const StringKey& key, const Json& value);
            Object(const std::initializer_list<std::pair<StringKey, Json>> &list);

            void add(const StringKey& key, const Json& value);

            Json& operator[](const StringKey& key);

            std::string to_string(bool format, size_t _tab_spaces = 4, size_t _count_of_indent = 0) const;

            size_t from_string(std::string_view str, size_t _index = 0);
        private:
            std::unordered_map<std::string, Json> m_map;
        };
    }
}

#endif//!R8GE_OBJECT_H
