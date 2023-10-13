#include "Json.h"

namespace r8ge {
    namespace Reader {

        FileType Json::getType() {
            return FileType::JSON;
        }

        Json::Json(const std::string &path) : Text(path) {
            write("{}");
        }

        Json::~Json() {}

        utility::Json &Json::json() {
            return m_json;
        }

        void Json::save_json() {
            write(m_json.to_string(true));
            save();
        }

        void Json::load_json() {
            load();
        }
    }
}