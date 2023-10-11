#ifndef R8GE_BINARY_H
#define R8GE_BINARY_H

#include "../FileReader.h"

#include <vector>

namespace r8ge {
    namespace Reader {
        class Binary : public FileReader {
        public:
            Binary(const std::string& path);
            ~Binary() override;

            void copyTo(void* buffer, size_t buffer_size);
            void copyTo(std::vector<unsigned char>& buffer);

            void copyFrom(const void* buffer, size_t buffer_size);
            void copyFrom(const std::vector<unsigned char>& buffer);

            static FileType getType();
        };
    }
}

#endif//!R8GE_BINARY_H
