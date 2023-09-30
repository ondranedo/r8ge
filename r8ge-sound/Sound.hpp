//
// Created by Wiszc on 24.09.2023.
//

#ifndef R8GE_SOUND_HPP
#define R8GE_SOUND_HPP
#include <audioclient.h>
#include <chrono>

namespace r8ge {
    int soundtestfunc();

    class MyAudioSource{
    public:
        HRESULT LoadData(UINT32 bufferFrameCount, BYTE *pData, DWORD* flags);
        HRESULT SetFormat(WAVEFORMATEX *pwfx);
    private:
        WAVEFORMATEX m_wfx = {};
        double m_generatedTime = 0.0;
    };
    HRESULT PlayAudioStream(MyAudioSource *pMySource);
}

#endif //R8GE_SOUND_HPP
