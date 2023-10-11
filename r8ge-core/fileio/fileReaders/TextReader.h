#ifndef R8GE_TEXTREADER_H
#define R8GE_TEXTREADER_H

#include "../FileReader.h"

#include <vector>

namespace r8ge {
    namespace Reader {
        class Text : public FileReader {
        public:
            Text(const std::string& path);
            ~Text() override;

            void save() const override;
            void load() override;

            [[nodiscard]] std::string readFile() const;
            [[nodiscard]] std::vector<std::string> readLines() const;

            static FileType getType();
        };
    }
}

#endif//!R8GE_TEXTREADER_H
