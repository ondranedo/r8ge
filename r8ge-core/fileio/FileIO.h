#ifndef R8GE_FILEIO_H
#define R8GE_FILEIO_H

#include <unordered_map>
#include <string>
#include <mutex>
#include <vector>

#include "FileType.h"

namespace r8ge {
    using byte = unsigned char;

    class FileIO final {
    public:
        FileIO(size_t filelimit);
        ~FileIO();

        void add(const std::string& path, FileType ft);
        void save(const std::string& path);
        void load(const std::string& path);
        void remove(const std::string& path);

        [[nodiscard]] size_t getFileCount();
        [[nodiscard]] size_t getFileLimit();
        [[nodiscard]] bool isFilePresent(const std::string& path);
        [[nodiscard]] size_t getFileSize(const std::string& path);
        [[nodiscard]] size_t getTotalSize();

        [[nodiscard]] std::string getTextData(const std::string& path);
        [[nodiscard]] std::vector<byte> getBinaryData(const std::string& path);

        void setTextData(const std::string& path, const std::string& data);
        void setBinaryData(const std::string& path, const std::vector<byte>& data);

        [[nodiscard]] bool isBinary(const std::string& path);
        [[nodiscard]] bool isText(const std::string& path);

        [[nodiscard]] std::vector<std::string> getTxtFiles();
        [[nodiscard]] std::vector<std::string> getBinFiles();
    private:

        std::unordered_map<std::string, std::string> m_txtFileMap;
        std::unordered_map<std::string, std::vector<byte>> m_binFileMap;
        std::unordered_map<std::string, FileType> m_fileTypeMap;
        std::unordered_map<std::string, bool> m_modifiedMap;

        const size_t m_fileLimit;
        size_t m_fileCount;
        std::mutex m_mutex;
    };

    namespace global{
        extern FileIO* fileIO;
    }
}

#endif//!R8GE_FILEIO_H
