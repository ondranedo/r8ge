//
// Created by Wiszc on 24.09.2023.
//

#ifndef R8GE_SOUND_HPP
#define R8GE_SOUND_HPP
#include <audioclient.h>
#include <chrono>
#include <mmdeviceapi.h>
#include "Generators.hpp"
#include <thread>


namespace r8ge {
    class AudioPusher{
    public:
        AudioPusher();
        ~AudioPusher();

        void stopSound();
        std::vector<Sound *> *getSoundVector();
        [[nodiscard]] double getGeneratedTime() const;
        void addSound(Sound* sound);
    private:
        WAVEFORMATEX* m_wfx = NULL;
        double m_generatedTime = 0.0;
        IMMDeviceEnumerator *m_pEnumerator = NULL;
        IMMDevice *m_pDevice = NULL;
        IAudioClient *m_pAudioClient = NULL;
        IAudioRenderClient *m_pRenderClient = NULL;
        DWORD m_flags = 0;
        std::vector<Sound*> m_activeSounds = {};
        std::mutex m_soundVectorGuard;

    private:

        HRESULT LoadData(UINT32 bufferFrameCount, BYTE *pData);
        void mainLoop();
        double sumSoundsAndRemove(unsigned char channel);

        std::thread m_mainLoop;
    };

}

#endif //R8GE_SOUND_HPP
