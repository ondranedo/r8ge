#ifndef R8GE_VALUE_H
#define R8GE_JSON_H

#include "Text.h"

namespace r8ge {
    namespace Reader {
        class Value : private Text {
        public:
            Value(const std::string& path);
            ~Value() override;

            static FileType getType();
        };
    }
}

#endif//!R8GE_VALUE_H
