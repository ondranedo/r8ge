//
// Created by Wiszc on 17.10.2023.
//

#ifndef R8GE_WAVE_HPP
#define R8GE_WAVE_HPP

#include "Binary.h"

namespace r8ge {

    // definition is in Generators; included here because I don't want
    struct WaveData{
        unsigned short m_format;
        unsigned short m_channels;
        unsigned long m_sampleRate;
        unsigned short m_blockAlign;
        double m_timeStep;

        unsigned long m_sampleCount;
        char* m_data; // takes up to megabytes but allows for instant skipping
        void fromVec(std::vector<unsigned char> vec);
    };

    namespace reader {
        class Wave : protected Binary {
        public:
            Wave(std::string_view path);
            ~Wave() override;

            WaveData& wave();
            void load_wave();

            static FileType getType();
        private:
            WaveData m_wave{};
        };
    }
}

#endif //R8GE_WAVE_HPP
