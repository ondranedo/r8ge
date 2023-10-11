#ifndef R8GE_BINARY_H
#define R8GE_BINARY_H

#include "../FileReader.h"

namespace r8ge {
    namespace Reader {
        class Binary : public FileReader {
        public:
            Binary(const std::string& path);
            ~Binary() override;



            static FileType getType();
        };
    }
}

#endif//!R8GE_BINARY_H
