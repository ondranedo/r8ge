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

            static FileType getType();
        };
    }
}

#endif//!R8GE_TEXT_H
