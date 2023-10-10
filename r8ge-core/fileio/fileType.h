#ifndef R8GE_FILETYPE_H
#define R8GE_FILETYPE_H

#include <string>

namespace r8ge {
    class fileType final {
    public:
        enum _type {
            JSON,
            TEXT,
            BINARY
        };

        fileType();
        fileType(fileType::_type ft);

        [[nodiscard]] std::string toString() const;


    private:
        _type m_type;
    };
}

#endif//!R8GE_FILETYPE_H
