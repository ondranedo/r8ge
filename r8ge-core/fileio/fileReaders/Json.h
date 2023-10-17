#ifndef R8GE_READER_JSON_H
#define R8GE_READER_JSON_H

#include "Text.h"

#include "../../utility/json/Json.h"

namespace r8ge {
    namespace Reader {
        class Json : protected Text {
        public:
            Json(const std::string& path);
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
