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

#define R8GE_LAST_SAMPLE_COUNT (1 << 11)

namespace r8ge {
    class AudioPusher{
    public:
        AudioPusher();
        ~AudioPusher();

        void stopSound();
        [[nodiscard]] double getGeneratedTime() const;
        void addSound(Sound* sound);
        float *newCurrentSamples();
    private:
#ifdef R8GE_WINDOWS
        WAVEFORMATEX* m_wfx = NULL;
        IMMDeviceEnumerator *m_pEnumerator = NULL;
        IMMDevice *m_pDevice = NULL;
        IAudioClient *m_pAudioClient = NULL;
        IAudioRenderClient *m_pRenderClient = NULL;
        DWORD m_flags = 0;
        HRESULT LoadData(UINT32 bufferFrameCount, BYTE *pData);
#endif

#ifdef R8GE_LINUX
        snd_pcm_t *m_pcmHandle;
        unsigned int m_nOfSamplesPerBuff = 256;
        unsigned int m_channels = 2;
        double m_timeStep;
        unsigned int m_nOfBuffers = 8;
        unsigned int m_rate = 48000;
        bool m_run = true;
#endif
        std::vector<Sound*> m_activeSounds = {};
        std::mutex m_soundVectorGuard;
        double m_generatedTime = 0.0;

        float* m_lastSamples = nullptr;
        int m_lastSamplesCount = R8GE_LAST_SAMPLE_COUNT;
        int m_lastSamplesCurr;

        void mainLoop();
        double sumSoundsAndRemove(unsigned char channel);

        std::thread m_mainLoop;
    };

}

#endif //R8GE_SOUND_HPP
