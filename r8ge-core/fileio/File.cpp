#include "File.h"

namespace r8ge {
    _File::_File(const std::string& path, FileType fileType) :
    m_path(path), m_fileMutex(), m_fileType(fileType) {}

    std::string _File::getPath() const {
        return m_path;
    }

    void _File::save(const FileReader* const fr) {
        m_fileMutex.lock();
        fr->save();
        m_fileMutex.unlock();
    }

    void _File::load(const FileReader* const fr) {
        m_fileMutex.lock();
        fr->load();
        m_fileMutex.unlock();
    }

    FileType _File::getFileType() const {
        return m_fileType;
    }

    _File::~_File() = default;

    File::File(const std::string& path, FileType ft) : _File(path, ft), m_file(FileReader::create(ft)) {}
}