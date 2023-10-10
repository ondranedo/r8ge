#ifndef R8GE_FILE_H
#define R8GE_FILE_H

#include <string>
#include <fstream>
#include <mutex>
#include <memory>
#include <variant>

#include "FileReader.h"
#include "FileType.h"
#include "../Logger.h"

#include "fileReaders/TextReader.h"

#include <concepts>

namespace r8ge {
    class _File {
    public:
        _File(const std::string& path, FileType ft = {});
        virtual ~_File();
        [[nodiscard]] std::string getPath() const;
        [[nodiscard]] FileType getFileType() const;

    private:
        std::string m_path;
        FileType m_fileType;
    };

    class File final : public _File {
    public:
        explicit File(const std::string& path, FileType ft = {});

        template <isFileReader T>
        [[nodiscard]] T& get() {
            if(T::getType()() != getFileType()()) {
                R8GE_LOG_ERROR("File type mismatch: expected `{}`, got `{}`", T::getType().toString(), getFileType().toString());
            }

            return *m_file;
        }

    private:
        std::unique_ptr<FileReader> m_file;
    };

    template<isFileReader T>
    class FileT final : public _File {
    public:
        explicit FileT(const std::string& path):
        _File(path, T::getType()()), m_file(std::make_unique<T>())
        {}

        [[nodiscard]] T& get() {
            return *m_file;
        }

        [[nodiscard]] T& operator()() {
            return *m_file;
        }
    private:
        std::unique_ptr<T> m_file;
    };
}

#endif//!R8GE_FILE_H
