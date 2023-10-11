#include "Binary.h"

#include "../FileIO.h"
#include "../../Core.h"

#include <cstring>

namespace r8ge {

    Reader::Binary::Binary(const std::string &path) : FileReader(path) {
        global::fileIO->add(m_path, FileType::BINARY);
    }

    Reader::Binary::~Binary() {
        global::fileIO->remove(m_path);
    }

    FileType Reader::Binary::getType() {
        return FileType::BINARY;
    }

    void Reader::Binary::copyTo(void *buffer, size_t buffer_size) {
        R8GE_ASSERT(buffer_size >= size(), "Buffer size is too small to copy file!");
        auto vec = global::fileIO->getBinaryData(m_path);
        std::memcpy(buffer, vec.data(), vec.size());
    }

    void Reader::Binary::copyTo(std::vector<unsigned char> &buffer) {
        buffer = global::fileIO->getBinaryData(m_path);
    }

    void Reader::Binary::copyFrom(const void* buffer, size_t buffer_size) {
        global::fileIO->setBinaryData(m_path,
                                      std::vector<unsigned char>(static_cast<const unsigned char*>(buffer),
                                                                 static_cast<const unsigned char*>(buffer) + buffer_size));
    }

    void Reader::Binary::copyFrom(const std::vector<unsigned char> &buffer) {
        global::fileIO->setBinaryData(m_path, buffer);
    }
}