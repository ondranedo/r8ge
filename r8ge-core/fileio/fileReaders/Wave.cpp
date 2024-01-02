//
// Created by Wiszc on 17.10.2023.
//

#include "Wave.hpp"
#include <iostream>
#include <cstring>

namespace r8ge {
    namespace reader {

        FileType Wave::getType() {
            return FileType::WAVE;
        }

        void Wave::load_wave() {
            std::vector<unsigned char> buff;
            load();
            read(buff);
            m_wave.fromVec(buff);
        }

        Wave::Wave(std::string_view path) : Binary(path) {

        }

        WaveData &Wave::wave() {
            return m_wave;
        }

        Wave::~Wave() = default;
    }

    void WaveData::fromVec(std::vector<unsigned char> vec) {
        char* cStringBuff = new char[5];
        cStringBuff[4] = '\0';
        std::string cmp;
        unsigned int u32Buff;
        unsigned int offset = 0;
        // this is just slower memcpy... shouldn't affect performance since it only is for loading
        auto loadStr = [cStringBuff, vec, &offset, &cmp](){
            for(int i = 0; i < 4; i++){
                cStringBuff[i] = *(vec.data() + offset);
                offset++;
            }
            cmp = cStringBuff;
        };

        loadStr();
        if(cmp != "RIFF"){
            std::cout << "File is not Wav" << std::endl;
            goto Exit;
        }

        u32Buff = *(unsigned int*)(vec.data() + offset);
        std::cout << "Size of file is " << u32Buff + 8 << " bytes" << std::endl;
        offset += 4;

        loadStr();
        if(cmp != "WAVE"){
            std::cout << "File is not Wav" << std::endl;
            goto Exit;
        }

        loadStr();
        if(cmp != "fmt "){
            std::cout << "File is corrupted" << std::endl;
            goto Exit;
        }

        u32Buff = *(unsigned int*)(vec.data() + offset);
        offset += 4;
        if(u32Buff != 16){
            std::cout << "File is corrupted" << std::endl;
            goto Exit;
        }

        m_format = *(short*)(vec.data() + offset);
        offset += 2;
        m_channels = *(short*)(vec.data() + offset);
        offset += 2;
        m_sampleRate = *(unsigned int*)(vec.data() + offset);
        offset += 4;
        m_timeStep = 1.0 / m_sampleRate;
        offset += 4;
        m_blockAlign = *(short*)(vec.data() + offset);
        offset += 2;
        offset += 2;

        loadStr();
        if(cmp != "data"){
            std::cout << "File is corrupted" << std::endl;
            goto Exit;
        }

        u32Buff = *(unsigned int*)(vec.data() + offset);
        offset += 4;
        m_sampleCount = u32Buff / m_blockAlign;

        m_data = new char[u32Buff];
        std::memcpy(m_data, vec.data(), u32Buff);

        Exit:
        delete[] cStringBuff;
    }
}