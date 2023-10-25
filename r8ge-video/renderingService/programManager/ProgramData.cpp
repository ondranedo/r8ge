#include "ProgramData.h"

namespace r8ge {
    namespace video {

        ProgramData::ProgramData(std::string_view location, const std::vector<uint8_t> &data, ProgramData::Type type)
        : m_location(location), m_type(type), m_data(data)
        {}

        std::string ProgramData::getLocation() const {
            return m_location;
        }


        ProgramData::Type ProgramData::getType() const {
            return m_type;
        }

        std::vector<uint8_t> ProgramData::getData() const {
            return m_data;
        }
    }
}