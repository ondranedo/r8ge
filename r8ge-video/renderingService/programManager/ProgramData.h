#ifndef R8GE_PROGRAMDATA_H
#define R8GE_PROGRAMDATA_H

#include <string>
#include <vector>
#include <cstdint>

namespace r8ge {
    namespace video {
        class ProgramData {
        public:
            enum class Type {
                NONE,
                VEC1, VEC2, VEC3, VEC4,
            };

            ProgramData(std::string_view location, const std::vector<uint8_t>& data, Type type);

            [[nodiscard]] std::string getLocation() const;

            [[nodiscard]] std::vector<uint8_t> getData() const;

            [[nodiscard]] Type getType() const;
        private:
            Type m_type;
            std::string m_location;
            std::vector<uint8_t> m_data;
        };
    }
}

#endif//!R8GE_PROGRAMDATA_H
