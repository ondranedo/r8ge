//
// Created by Wiszc on 24.09.2023.
//

#define R8GE_LINUX // todo: for dev purposes, remove later
#ifndef R8GE_SOUND_HPP
#define R8GE_SOUND_HPP
#ifdef R8GE_WINDOWS
    #include <audioclient.h>
    #include <mmdeviceapi.h>
#endif
#ifdef R8GE_LINUX
    #include <alsa/asoundlib.h>
#endif
#include <chrono>
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
#ifdef R8GE_WINDOWS
        WAVEFORMATEX* m_wfx = NULL;
        IMMDeviceEnumerator *m_pEnumerator = NULL;
        IMMDevice *m_pDevice = NULL;
        IAudioClient *m_pAudioClient = NULL;
        IAudioRenderClient *m_pRenderClient = NULL;
        DWORD m_flags = 0;
#endif

        std::vector<Sound*> m_activeSounds = {};
        std::mutex m_soundVectorGuard;
        double m_generatedTime = 0.0;

    private:
#ifdef R8GE_WINDOWS
        HRESULT LoadData(UINT32 bufferFrameCount, BYTE *pData);
#endif
        void mainLoop();
        double sumSoundsAndRemove(unsigned char channel);

        std::thread m_mainLoop;
    };

}

#endif //R8GE_SOUND_HPP
