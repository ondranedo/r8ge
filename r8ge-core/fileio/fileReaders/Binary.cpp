#include "Binary.h"

#include "../FileIO.h"

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
}