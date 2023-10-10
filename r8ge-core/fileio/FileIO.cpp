#include "FileIO.h"

#include <fstream>

#include "../Logger.h"
#include "../Core.h"

namespace r8ge {
    namespace global {
        FileIO* fileIO = nullptr;
    }

    FileIO::FileIO(size_t filelimit) : m_fileCount(0), m_fileLimit(filelimit) {}

    FileIO::~FileIO() {
        R8GE_LOG_WARNI("FileIO is being destroyed, {} files were not removed", m_fileCount);

        auto txt = getTxtFiles();
        for(auto& path : txt)
            remove(path);

        auto bin = getBinFiles();
        for(auto& path : bin)
            remove(path);
        R8GE_ASSERT(m_fileCount==0, "FileIO is not empty on destruction");
    }

    void FileIO::add(const std::string &path, FileType ft) {
        if(m_txtFileMap.find(path) != m_txtFileMap.end() || m_binFileMap.find(path) != m_binFileMap.end())
        {
            R8GE_LOG_WARNI("file {} is already present in FileIO", path);
            return;
        }

        // TODO: Check file limit

        if(ft()==FileType::TEXT) {
            m_mutex.lock();
            m_txtFileMap[path] = "";
            m_fileTypeMap[path] = ft;
            m_fileCount++;
            m_modifiedMap[path] = false;
            m_mutex.unlock();
        }
        else if(ft()==FileType::BINARY) {
            m_mutex.lock();
            m_binFileMap[path] = std::vector<byte>();
            m_fileTypeMap[path] = ft;
            m_fileCount++;
            m_modifiedMap[path] = false;
            m_mutex.unlock();
        }
        else {
            R8GE_LOG_ERROR("Other than [FileType::BINARY/FileType::TEXT] file type passed to FileIO::save()");
        }
    }

    void FileIO::save(const std::string &path) {
        if(!isFilePresent(path)) return;

        if(isBinary(path)) {
            m_mutex.lock();
            std::ofstream file(path, std::ios::binary);
            file.write((char*)m_binFileMap[path].data(), m_binFileMap[path].size());
            file.close();
            m_mutex.unlock();
        }
        else
        {
            m_mutex.lock();
            std::ofstream file(path);
            file << m_txtFileMap[path];
            file.close();
            m_mutex.unlock();
        }

        m_mutex.lock();
        m_modifiedMap[path] = false;
        m_mutex.unlock();
    }

    void FileIO::load(const std::string &path) {
        if(!isFilePresent(path)) return;

        if(isBinary(path)) {
            m_mutex.lock();
            std::ifstream file(path, std::ios::binary);
            std::vector<byte> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            m_binFileMap[path] = data;
            m_modifiedMap[path] = false;
            file.close();
            m_mutex.unlock();
        }
        else
        {
            m_mutex.lock();
            std::ifstream file(path);
            std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            m_txtFileMap[path] = data;
            m_modifiedMap[path] = false;
            file.close();
            m_mutex.unlock();
        }
    }

    void FileIO::remove(const std::string &path) {
        if(!isFilePresent(path)) return;

        if(isText(path)) {
            m_mutex.lock();
            m_fileCount--;
            if(m_modifiedMap[path])
                R8GE_LOG_WARNI("Text file {} was not saved", path);
            m_txtFileMap.erase(path);
            m_mutex.unlock();
        } else {
            m_mutex.lock();
            m_fileCount--;
            if(m_modifiedMap[path])
                R8GE_LOG_WARNI("Binary file {} was not saved", path);
            m_binFileMap.erase(path);
            m_mutex.unlock();
        }
    }

    size_t FileIO::getFileCount() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileCount;
    }

    size_t FileIO::getFileLimit() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileLimit;
    }

    bool FileIO::isFilePresent(const std::string &path) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(m_txtFileMap.find(path) != m_txtFileMap.end()) return true;
        if(m_binFileMap.find(path) != m_binFileMap.end()) return true;

        R8GE_LOG_WARNI("file {} is not present in FileIO", path);

        return false;
    }

    size_t FileIO::getFileSize(const std::string& path){
        if(!isFilePresent(path)) return 0;

        if(isText(path)) {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_txtFileMap[path].size();
        }

        if(isBinary(path)) {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_binFileMap[path].size();
        }

        return 0;
    }

    size_t FileIO::getTotalSize(){
        size_t totalSize = 0;

        m_mutex.lock();
        for(auto& [path, data] : m_txtFileMap)
            totalSize += data.size();
        for(auto& [path, data] : m_binFileMap)
            totalSize += data.size();
        m_mutex.unlock();

        return totalSize;
    }

    bool FileIO::isBinary(const std::string &path) {
        if(!isFilePresent(path)) return false;
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileTypeMap[path]() == FileType::BINARY;
    }

    std::string FileIO::getTextData(const std::string &path) {
        if(!isFilePresent(path)) return "";
        if(!isText(path))
        {
            R8GE_LOG_ERROR("Trying to get text data from a binary file: {}", path);
            return "";
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        return m_txtFileMap[path];
    }

    std::vector<byte> FileIO::getBinaryData(const std::string &path) {
        if(!isFilePresent(path)) return{};
        if(!isBinary(path))
        {
            R8GE_LOG_ERROR("Trying to get binary data from a text file: {}", path);
            return{};
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        return m_binFileMap[path];
    }

    bool FileIO::isText(const std::string &path) {
        return !isBinary(path);
    }

    std::vector<std::string> FileIO::getTxtFiles() {
        std::vector<std::string> txtFiles;
        std::lock_guard<std::mutex> lock(m_mutex);
        for(auto& [path, _] : m_txtFileMap)
            txtFiles.push_back(path);
        return txtFiles;
    }

    std::vector<std::string> FileIO::getBinFiles() {
        std::vector<std::string> binFiles;
        std::lock_guard<std::mutex> lock(m_mutex);
        for(auto& [path, _] : m_binFileMap)
            binFiles.push_back(path);
        return binFiles;
    }

    void FileIO::setTextData(const std::string &path, const std::string &data) {
        if(!isFilePresent(path)) return;
        std::lock_guard<std::mutex> lock(m_mutex);
        m_txtFileMap[path] = data;
        m_modifiedMap[path] = true;
    }

    void FileIO::setBinaryData(const std::string &path, const std::vector<byte> &data) {
        if(!isFilePresent(path)) return;
        std::lock_guard<std::mutex> lock(m_mutex);
        m_binFileMap[path] = data;
        m_modifiedMap[path] = true;
    }
}