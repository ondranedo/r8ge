
#ifndef R8GE_STRINGFORMAT_H
#define R8GE_STRINGFORMAT_H

#include <variant>
#include <string>

namespace r8ge {
    namespace utility {
        /*
         * StringFormat is a utility class which provides the ability tu use
         * very basic `fmt-like` string formats.
         *
         * example:
         *  StringFormat("{1}, {0}!", {"World", "Hello"}) -> "Hello, World!"
         *  StringFormat("{}, {}! {}", {"World", "Hello"}) -> "World, Hello! "Hello"
         *  StringFormat("{} {} {}", {1, 2, 3}) -> "1 2 3"
         *  StringFormat("{0} {} {} {1}", {"Ahoj", 1, 2}) -> "Ahoj Ahoj 1 1"
         *  StringFormat("{}{}{}", {'a'}) -> "aaa"
         *  StringFormat("{0};{1};{2}", {10, 20}) -> "10;20;{missing_value}"
         *  StringFormat("{}, {}, {}, {}", {1,2}) -> "1, 2, 2, 2"
         */

        class StringFormat {
        public:
            // Data types that can be formatted into string
            using ValidType = std::variant<
                    int, float, std::string, char
                    >;
            using ValidList = std::initializer_list<ValidType>;
            StringFormat(const std::string& form, const ValidList& list);
            StringFormat(const std::string& str);
            StringFormat();

            [[nodiscard]] std::string to_string();

        private:
            std::string m_str;
        };
    }
}

#endif//!R8GE_STRINGFORMAT_H
