#ifndef R8GE_BINARY_H
#define R8GE_BINARY_H

#include "../FileReader.h"

#include <vector>

namespace r8ge {
    namespace Reader {
        class Binary : public FileReader {
        public:
            Binary(std::string_view path);
            ~Binary() override;

            void read(void* buffer, size_t buffer_size);
            void read(std::vector<unsigned char>& buffer);

            void write(const void* buffer, size_t buffer_size);
            void write(const std::vector<unsigned char>& buffer);

            void append(const void* buffer, size_t buffer_size);
            void append(const std::vector<unsigned char>& buffer);
            void append(unsigned char c);

            static FileType getType();
        };
    }
}

#endif//!R8GE_BINARY_H
