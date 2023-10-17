//
// Created by Wiszc on 17.10.2023.
//

#ifndef R8GE_WAVE_HPP
#define R8GE_WAVE_HPP

#include "Binary.h"

namespace r8ge {

    // todo: move to sound once merged
    struct Wave{
        void fromVec();
    };

    namespace Reader {
        class Wave : protected Binary {
        public:
            Wave(std::string_view path);
            ~Wave() override;

            ::r8ge::Wave& wave();
            void load_wave();

            static FileType getType();
        private:
            ::r8ge::Wave m_wave;
        };
    }
}

#endif //R8GE_WAVE_HPP
