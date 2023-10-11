#include "FileReader.h"

#include "../Core.h"

#include "fileReaders/Text.h"
#include "FileIO.h"

namespace r8ge {
    FileReader::FileReader(const std::string& path) : m_path(path) {}
    FileReader::~FileReader() = default;

    std::unique_ptr<FileReader> FileReader::create(const FileType &ft, const std::string& path) {
        switch (ft()) {
           case FileType::TEXT: return std::make_unique<Reader::Text>(path);

           case FileType::JSON:
           case FileType::BINARY:
               R8GE_ASSERT(false, "FileReader {} implemented", ft.toString());
               return nullptr;
        }

        R8GE_ASSERT(false, "Unknown file type");
        return nullptr;
    }

    void FileReader::save() const {
        global::fileIO->save(m_path);
    }

    void FileReader::load() const {
        global::fileIO->load(m_path);
    }

    size_t FileReader::size() const {
        return global::fileIO->getFileSize(m_path);
    }
}