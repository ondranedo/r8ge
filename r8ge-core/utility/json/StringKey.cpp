#include "StringKey.h"

namespace r8ge {
    namespace utility {
        StringKey::StringKey(const std::string &str) {
            m_string = str;
        }

        StringKey::StringKey(const char *str) {
            m_string = str;
        }

        std::string StringKey::get() const {
            return m_string;
        }

        namespace literals {
            StringKey operator "" _k(const char *str, size_t) {
                return StringKey(str);
            }
        }
    }
}