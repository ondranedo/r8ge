#include "file.h"

namespace r8ge {
    file::file(const std::string& path, fileType fileType) :
    m_path(path), m_file{}, m_fileMutex(), m_fileType(fileType) {
        //m_file = std::make_unique<fileReader>(path);
    }

    std::string file::getPath() const {
        return m_path;
    }

    void file::save() {
        m_fileMutex.lock();
        m_file->save();
        m_fileMutex.unlock();
    }

    void file::load() {
        m_fileMutex.lock();
        m_file->load();
        m_fileMutex.unlock();
    }
}