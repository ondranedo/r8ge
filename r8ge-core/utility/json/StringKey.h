#ifndef R8GE_STRINGKEY_H
#define R8GE_STRINGKEY_H

#include <string>

namespace r8ge {
    namespace utility {
        class StringKey {
        public:
            StringKey(const std::string& str);
            StringKey(const char* str);

            std::string get() const;
        private:
            std::string m_string;
        };

        namespace literals {
            StringKey operator"" _k(const char* str, size_t);
        }
    }
}

#endif//!R8GE_STRINGKEY_H
