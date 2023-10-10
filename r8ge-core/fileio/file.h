#ifndef R8GE_FILE_H
#define R8GE_FILE_H

#include <string>
#include <fstream>
#include <mutex>
#include <memory>

#include "fileReader.h"
#include "fileType.h"

namespace r8ge {
    class file final {
    public:
        file(const std::string& path, fileType ft = {});

        void save();
        void load();

        [[nodiscard]] std::string getPath() const;

    private:
        std::string m_path;
        std::mutex m_fileMutex;
        std::unique_ptr<fileReader> m_file;
        fileType m_fileType;
    };
}

#endif//!R8GE_FILE_H
