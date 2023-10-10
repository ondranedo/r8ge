#include "FileReader.h"

#include "../Core.h"

#include "fileReaders/TextReader.h"

namespace r8ge {

    FileReader::~FileReader() = default;

    std::unique_ptr<FileReader> FileReader::create(const FileType &ft) {
        switch (ft()) {
           case FileType::TEXT: return std::make_unique<Reader::Text>();

           case FileType::JSON:
           case FileType::BINARY:
               R8GE_ASSERT(false, "FileReader {} implemented", ft.toString());
               return nullptr;
        }

        R8GE_ASSERT(false, "Unknown file type");
        return nullptr;
    }
}