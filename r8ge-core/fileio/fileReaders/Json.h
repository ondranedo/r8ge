#ifndef R8GE_READER_JSON_H
#define R8GE_READER_JSON_H

#include "Text.h"

#include "../../utility/json/Json.h"

namespace r8ge {
    namespace reader {
        class Json : protected Text {
        public:
            Json(std::string_view path);
            ~Json() override;

            utility::Json& json();
            void save_json();
            void load_json();

            static FileType getType();
        private:
            utility::Json m_json;
        };
    }
}

#endif//!R8GE_READER_JSON_H
