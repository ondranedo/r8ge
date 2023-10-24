#include "Json.h"

namespace r8ge {
    namespace reader {

        FileType Json::getType() {
            return FileType::JSON;
        }

        Json::Json(std::string_view path) : Text(path) {
            write("{}");
        }

        Json::~Json() {}

        utility::Json &Json::json() {
            return m_json;
        }

        void Json::save_json() {
            write(m_json.to_string(true));
            save();
            write("");
        }

        void Json::load_json() {
            load();
            m_json.from_string(readFile());
            write("");
        }
    }
}