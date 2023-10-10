#ifndef R8GE_TEXTREADER_H
#define R8GE_TEXTREADER_H

#include "../FileReader.h"

namespace r8ge {
    namespace Reader {
        class Text : public FileReader {
        public:
            ~Text() override;

            void save() const override;
            void load() const override;

            std::string readFile() const;

            static FileType getType();
        };
    }
}

#endif//!R8GE_TEXTREADER_H
