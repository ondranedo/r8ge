#include "Json.h"

namespace r8ge {
    namespace Reader {

        FileType Value::getType() {
            return FileType::JSON;
        }

        Value::Value(const std::string &path) : Text(path) {}

        Value::~Value() {}
    }
}