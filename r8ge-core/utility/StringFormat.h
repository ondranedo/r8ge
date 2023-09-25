#ifndef R8GE_STRINGFORMAT_H
#define R8GE_STRINGFORMAT_H

#include <variant>
#include <string>

namespace r8ge {
    namespace utility {
        class StringFormat {
        public:
            // Data types that can be formatted into string
            using ValidType = std::variant<
                    int, float, std::string, char, char*
                    >;
            using ValidList = std::initializer_list<ValidType>;
            StringFormat(const std::string& form, const ValidList& list);
            StringFormat(const std::string& str);
            StringFormat();

            [[nodiscard]] std::string to_string();
            operator std::string();

        private:
            std::string m_str;
        };
    }
}

#endif//!R8GE_STRINGFORMAT_H
