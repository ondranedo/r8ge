//
// Created by Wiszc on 17.10.2023.
//

#include "Wave.hpp"

namespace r8ge {
    namespace Reader {

        FileType Wave::getType() {
            return FileType::WAVE;
        }

        ::r8ge::Wave &Wave::wave() {
            return m_wave;
        }

        void Wave::load_wave() {
            std::vector<unsigned char> buff;
            load();
            read(buff);
            m_wave.fromVec(buff);
        }

        Wave::Wave(std::string_view path) : Binary(path) {

        }

        Wave::~Wave() = default;
    }
}