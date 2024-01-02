//
// Created by Wiszc on 24.09.2023.
//

#include "Sound.hpp"
#include <iostream>
#include <cmath>

#include <cstring>

#define R8GE_MAIN_VOLUME 0.02

#ifdef R8GE_WINDOWS

#include <cstdlib>
#include <random>

// credit: someone on learn.microsoft
//-----------------------------------------------------------
// Play an audio stream on the default audio rendering
// device. The PlayAudioStream function allocates a shared
// buffer big enough to hold one second of PCM audio data.
// The function uses this buffer to stream data to the
// rendering device. The inner loop runs every 1/2 second.
//-----------------------------------------------------------

// REFERENCE_TIME time units per second and per millisecond
#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define LOG_AND_EXIT_ON_ERROR(hres, text) \
                        if(FAILED(hres)){ std::cout << (text) << std::endl; goto Exit;}
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

r8ge::AudioPusher::AudioPusher() {
    HRESULT hr;
    REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;

    hr = CoInitialize(NULL);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to initialize the COM library")

    hr = CoCreateInstance(
            CLSID_MMDeviceEnumerator, NULL,
            CLSCTX_ALL, IID_IMMDeviceEnumerator,
            (void**)&m_pEnumerator);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to create a device enumerator")

    hr = m_pEnumerator->GetDefaultAudioEndpoint(
            eRender, eConsole, &m_pDevice);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to get the default audio output")

    hr = m_pDevice->Activate(
            IID_IAudioClient, CLSCTX_ALL,
            NULL, (void**)&m_pAudioClient);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to create an audio client")

    hr = m_pAudioClient->GetMixFormat(&m_wfx);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to gain information on the used format")

    hr = m_pAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            0,
            hnsRequestedDuration,
            0,
            m_wfx,
            NULL);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to initialize the audio client")

    hr = m_pAudioClient->GetService(
            IID_IAudioRenderClient,
            (void**)&m_pRenderClient);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to create the audio renderer")

    hr = m_pAudioClient->Start();  // Start playing.
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to start playing audio")

    m_mainLoop = std::thread(&AudioPusher::mainLoop, this);

    Exit:
}

void r8ge::AudioPusher::mainLoop() {
    UINT32 numFramesAvailable;
    UINT32 numFramesPadding;
    BYTE *pData;
    REFERENCE_TIME hnsActualDuration;
    UINT32 bufferFrameCount;
    HRESULT hr;

    // Get the actual size of the allocated buffer.
    hr = m_pAudioClient->GetBufferSize(&bufferFrameCount);
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to get info about the allocated audio buffer")

    // Calculate the actual duration of the allocated buffer.
    hnsActualDuration = (double)REFTIMES_PER_SEC *
                        bufferFrameCount / m_wfx->nSamplesPerSec;

    // Each loop fills about half of the shared buffer.
    while (m_flags != AUDCLNT_BUFFERFLAGS_SILENT) {

// See how much buffer space is available.
        hr = m_pAudioClient->GetCurrentPadding(&numFramesPadding);
        LOG_AND_EXIT_ON_ERROR(hr, "Failed to get information about the buffer padding")

        numFramesAvailable = bufferFrameCount - numFramesPadding;

// Grab all the available space in the shared buffer.
        hr = m_pRenderClient->GetBuffer(numFramesAvailable, &pData);
        LOG_AND_EXIT_ON_ERROR(hr, "Failed to get the available audio buffer")

// Get next 1/2-second of data from the audio source.
        hr = this->LoadData(numFramesAvailable, pData);
        LOG_AND_EXIT_ON_ERROR(hr, "Failed to load data into the audio buffer")

        hr = m_pRenderClient->ReleaseBuffer(numFramesAvailable, m_flags);
        LOG_AND_EXIT_ON_ERROR(hr, "Failed to free the filled audio buffer")

        Sleep((DWORD) (hnsActualDuration / REFTIMES_PER_MILLISEC / 2));
    }

    hr = m_pAudioClient->Stop();  // Stop playing.
    LOG_AND_EXIT_ON_ERROR(hr, "Failed to stop playing audio for some reason")

    Exit:
}

// note to self: all this should do is load correct sound data to a buffer
HRESULT r8ge::AudioPusher::LoadData(UINT32 bufferFrameCount, BYTE *pData) {
    switch(m_wfx->wBitsPerSample){
        case 32:
            switch(m_wfx->cbSize){
                case 22:
                    for(int i = 0; i < bufferFrameCount; i++){
                        for(unsigned char j = 0; j < m_wfx->nChannels; j++) {
                            *((float*)pData + (i * m_wfx->nChannels) + j) = (float)(sumSoundsAndRemove(j) * R8GE_MAIN_VOLUME);
                        }
                        m_generatedTime +=  1.0 / m_wfx->nSamplesPerSec;
                    }
                    break;
                default:
                    m_flags |= AUDCLNT_BUFFERFLAGS_SILENT;
            }
            break;
        default: m_flags |= AUDCLNT_BUFFERFLAGS_SILENT;
    }
    return 0;
}


void r8ge::AudioPusher::stopSound() {
    m_flags |= AUDCLNT_BUFFERFLAGS_SILENT;
}

r8ge::AudioPusher::~AudioPusher() {
    m_mainLoop.join();
    CoTaskMemFree(m_wfx);
    SAFE_RELEASE(m_pEnumerator)
    SAFE_RELEASE(m_pDevice)
    SAFE_RELEASE(m_pAudioClient)
    SAFE_RELEASE(m_pRenderClient)
}

#endif // R8GE_WINDOWS
#ifdef R8GE_LINUX
// Alessandro Ghedini helped write this portion of the code

#define PCM_DEVICE "default"

r8ge::AudioPusher::AudioPusher() {
    int err;

    m_timeStep = 1.0 / m_rate;

    /* Open the PCM device in playback mode */
    if (snd_pcm_open(&m_pcmHandle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0) < 0){
        R8GE_LOG_ERROR("ERROR: Can't open {} PCM device. {}", std::string(PCM_DEVICE), std::string(snd_strerror(err)));
        goto Exit;
    }

    err = snd_pcm_set_params(m_pcmHandle,
                             SND_PCM_FORMAT_FLOAT,
                             SND_PCM_ACCESS_RW_INTERLEAVED,
                             m_channels,
                             m_rate,
                             1,
                             1000000 * m_timeStep * m_nOfSamplesPerBuff * m_nOfBuffers);

    if(err < 0){
        R8GE_LOG_ERROR("ERROR: Can't set sound parameters: {}",  snd_strerror(err));
    }

    m_lastSamples = new float[m_lastSamplesCount];
    m_lastSamplesCurr = 0;

    m_mainLoop = std::thread(&AudioPusher::mainLoop, this);

    snd_pcm_start(m_pcmHandle);

    Exit:
}

r8ge::AudioPusher::~AudioPusher() {
    m_mainLoop.join();
    delete[] m_lastSamples;
}

void r8ge::AudioPusher::stopSound() {
    m_run = false;
}

void r8ge::AudioPusher::mainLoop() {
    /* Allocate buffer to hold single period */
    unsigned int buff_size = 4 /*float*/ * m_nOfSamplesPerBuff * m_channels;
    char* buff = new char[buff_size];
    float sum, chan;

    while(m_run){
        for (int i = 0; i < m_nOfSamplesPerBuff; i++) {
            sum = 0;
            for (int j = 0; j < m_channels; j++) {
                chan = (float)(sumSoundsAndRemove(j) * R8GE_MAIN_VOLUME);
                *((float*) buff + i * m_channels + j) = chan;
                sum += chan;
            }
            m_lastSamples[m_lastSamplesCurr++] = sum;
            if(m_lastSamplesCurr == m_lastSamplesCount){
                m_lastSamplesCurr = 0;
            }
            m_generatedTime += m_timeStep;
        }
        snd_pcm_writei(m_pcmHandle, buff, m_nOfSamplesPerBuff);
    }

    snd_pcm_drain(m_pcmHandle);
    snd_pcm_close(m_pcmHandle);
    delete[] buff;
}

#endif // R8GE_LINUX

double r8ge::AudioPusher::sumSoundsAndRemove(unsigned char channel){
    if(m_isPaused){
        return 0.0;
    }
    const std::lock_guard<std::mutex> lock(m_soundVectorGuard);
    double res = 0.0;
    int i = 0;
    bool states[m_activeSounds.size()];

    for(auto& g : m_activeSounds){
        res += g->generate(m_generatedTime, channel);
        states[i] = g->getState();
        i++;
    }
    i = 0;
    for(auto iter = m_activeSounds.begin(); iter != m_activeSounds.end();){
        if(!states[i]){
            iter = m_activeSounds.erase(iter);
        }
        else{
            iter++;
        }
        i++;
    }
    return res;
}

double r8ge::AudioPusher::getGeneratedTime() const {
    return m_generatedTime;
}

int r8ge::AudioPusher::addSound(r8ge::Sound *sound) {
    const std::lock_guard<std::mutex> lock(m_soundVectorGuard);
    m_count++;
    sound->setID(m_count);
    m_activeSounds.push_back(sound);
    return m_count;
}

float *r8ge::AudioPusher::newCurrentSamples() {
    auto r = new float[m_lastSamplesCount];
    std::memcpy(r, m_lastSamples, m_lastSamplesCount);
    return r;
}

void r8ge::AudioPusher::pause() {
    m_isPaused = true;
}

void r8ge::AudioPusher::play() {
    m_isPaused = false;
}

int r8ge::AudioPusher::playWave(const std::string &filename) {
    return addSound(new Wave(m_generatedTime ,filename));;
}

int r8ge::AudioPusher::playNote(short tone, double (*generator)(double), r8ge::Envelope envelope) {
    return addSound(new Note(m_generatedTime, tone, generator, envelope));
}

int r8ge::AudioPusher::playNote(short tone, r8ge::Instrument inst) {
    return addSound(new Note(m_generatedTime, tone, inst.m_generator, inst.m_envelope));
}

void r8ge::AudioPusher::deleteSound(int id) {
    for(auto& s : m_activeSounds){
        if(s->getID() == id){
            s->setEndTime(m_generatedTime);
            return;
        }
    }
}

/*
HRESULT r8ge::PlayAudioStream(MyAudioSource *pMySource)
{
    HRESULT hr;
    REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
    REFERENCE_TIME hnsActualDuration;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    IAudioClient *pAudioClient = NULL;
    IAudioRenderClient *pRenderClient = NULL;
    WAVEFORMATEX *pwfx = NULL;
    UINT32 bufferFrameCount;
    UINT32 numFramesAvailable;
    UINT32 numFramesPadding;
    BYTE *pData;
    DWORD flags = 0;

    hr = CoInitialize(NULL);
    EXIT_ON_ERROR(hr)

    hr = CoCreateInstance(
            CLSID_MMDeviceEnumerator, NULL,
            CLSCTX_ALL, IID_IMMDeviceEnumerator,
            (void**)&pEnumerator);
    EXIT_ON_ERROR(hr)

    hr = pEnumerator->GetDefaultAudioEndpoint(
            eRender, eConsole, &pDevice);
    EXIT_ON_ERROR(hr)

    hr = pDevice->Activate(
            IID_IAudioClient, CLSCTX_ALL,
            NULL, (void**)&pAudioClient);
    EXIT_ON_ERROR(hr)

    hr = pAudioClient->GetMixFormat(&pwfx);
    EXIT_ON_ERROR(hr)

    hr = pAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            0,
            hnsRequestedDuration,
            0,
            pwfx,
            NULL);
    EXIT_ON_ERROR(hr)

    // Tell the audio source which format to use.
    hr = pMySource->SetFormat(pwfx);
    EXIT_ON_ERROR(hr)

    // Get the actual size of the allocated buffer.
    hr = pAudioClient->GetBufferSize(&bufferFrameCount);
    EXIT_ON_ERROR(hr)

    hr = pAudioClient->GetService(
            IID_IAudioRenderClient,
            (void**)&pRenderClient);
    EXIT_ON_ERROR(hr)

    // Grab the entire buffer for the initial fill operation.
    hr = pRenderClient->GetBuffer(bufferFrameCount, &pData);
    EXIT_ON_ERROR(hr)

    // Load the initial data into the shared buffer.
    hr = pMySource->LoadData(bufferFrameCount, pData, &flags);
    EXIT_ON_ERROR(hr)

    hr = pRenderClient->ReleaseBuffer(bufferFrameCount, flags);
    EXIT_ON_ERROR(hr)

    // Calculate the actual duration of the allocated buffer.
    hnsActualDuration = (double)REFTIMES_PER_SEC *
                        bufferFrameCount / pwfx->nSamplesPerSec;

    hr = pAudioClient->Start();  // Start playing.
    EXIT_ON_ERROR(hr)

    // Each loop fills about half of the shared buffer.
    while (flags != AUDCLNT_BUFFERFLAGS_SILENT)
    {
        // Sleep for half the buffer duration.
        Sleep((DWORD)(hnsActualDuration/REFTIMES_PER_MILLISEC/2));

        // See how much buffer space is available.
        hr = pAudioClient->GetCurrentPadding(&numFramesPadding);
        EXIT_ON_ERROR(hr)

        numFramesAvailable = bufferFrameCount - numFramesPadding;

        // Grab all the available space in the shared buffer.
        hr = pRenderClient->GetBuffer(numFramesAvailable, &pData);
        EXIT_ON_ERROR(hr)

        // Get next 1/2-second of data from the audio source.
        hr = pMySource->LoadData(numFramesAvailable, pData, &flags);
        EXIT_ON_ERROR(hr)

        hr = pRenderClient->ReleaseBuffer(numFramesAvailable, flags);
        EXIT_ON_ERROR(hr)
    }

    // Wait for last data in buffer to play before stopping.
    Sleep((DWORD)(hnsActualDuration/REFTIMES_PER_MILLISEC/2));

    hr = pAudioClient->Stop();  // Stop playing.
    EXIT_ON_ERROR(hr)

    Exit:
    CoTaskMemFree(pwfx);
    SAFE_RELEASE(pEnumerator)
    SAFE_RELEASE(pDevice)
    SAFE_RELEASE(pAudioClient)
    SAFE_RELEASE(pRenderClient)

    return hr;
}
*/