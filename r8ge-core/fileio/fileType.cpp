#include "fileType.h"

namespace r8ge {
    std::string fileType::toString() const {
        switch (m_type) {
            case JSON:
                return "JSON";
            case TEXT:
                return "TEXT";
            case BINARY:
                return "BINARY";
        }
        return "UNKNOWN";
    }

    fileType::fileType() : m_type(TEXT) {}

    fileType::fileType(fileType::_type ft) : m_type(ft) {}
}