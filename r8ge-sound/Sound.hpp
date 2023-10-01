//
// Created by Wiszc on 24.09.2023.
//

#ifndef R8GE_SOUND_HPP
#define R8GE_SOUND_HPP
#include <audioclient.h>
#include <chrono>
#include <mmdeviceapi.h>

namespace r8ge {
    class AudioPusher{
    public:
        AudioPusher();
        ~AudioPusher();
    private:
        WAVEFORMATEX* m_wfx = NULL;
        double m_generatedTime = 0.0;
        IMMDeviceEnumerator *m_pEnumerator = NULL;
        IMMDevice *m_pDevice = NULL;
        IAudioClient *m_pAudioClient = NULL;
        IAudioRenderClient *m_pRenderClient = NULL;
        double (*m_generatorFunc)(double);

        HRESULT LoadData(UINT32 bufferFrameCount, BYTE *pData, DWORD* flags);
    };
}

#endif //R8GE_SOUND_HPP
