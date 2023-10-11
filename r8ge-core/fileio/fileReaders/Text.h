#ifndef R8GE_TEXT_H
#define R8GE_TEXT_H

#include "../FileReader.h"

#include <vector>

namespace r8ge {
    namespace Reader {
        class Text : public FileReader {
        public:
            Text(const std::string& path);
            ~Text() override;

            [[nodiscard]] std::string readFile() const;
            [[nodiscard]] std::vector<std::string> readLines() const;
            [[nodiscard]] size_t lineNumber() const;

            void write(const std::string& buffer);
            void write(const std::vector<std::string>& buffer);

            void append(const std::string& buffer);
            void append(const std::vector<std::string>& buffer);
            void append(char c);

            void appendNewLine();

            void appendNewLine(const std::string& buffer);
            void appendNewLine(const std::vector<std::string>& buffer);
            void appendNewLine(char c);


            static FileType getType();
        };
    }
}

#endif//!R8GE_TEXT_H
