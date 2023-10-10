#ifndef R8GE_FILEREADER_H
#define R8GE_FILEREADER_H

#include "FileType.h"

namespace r8ge {
    class FileReader {
    public:
        virtual ~FileReader() = 0;

        virtual void save() const = 0;
        virtual void load() const = 0;

    public:
        static std::unique_ptr<FileReader> create(const FileType& ft);
    };

    template <typename T>
    concept isFileReader = std::is_base_of_v<FileReader, T>;
}

#endif//!R8GE_FILEREADER_H
