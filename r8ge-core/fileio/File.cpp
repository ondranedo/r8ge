#include "File.h"

#include "FileIO.h"

namespace r8ge {
    _File::_File(const std::string& path, FileType fileType) :
    m_path(path), m_fileType(fileType) {}

    std::string _File::getPath() const {
        return m_path;
    }

    FileType _File::getFileType() const {
        return m_fileType;
    }

    void _File::copy(const std::string &path) {
        global::fileIO->copy(m_path, path);
    }

    _File::~_File() = default;
}