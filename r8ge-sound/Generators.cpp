//
// Created by Wiszc on 02.10.2023.
//

#include "Generators.hpp"

// should only output a value
double r8ge::Note::generate(double timeSecs, unsigned char channel) {
    double modifier;
    double activeTime = timeSecs - m_startTime;
    if(activeTime < 0){
        return 0.0;
    }
    if(activeTime < m_envelope.m_attackTime){
        modifier = (activeTime / m_envelope.m_attackTime) * m_envelope.m_maxVolume;
    }
    else if(activeTime < m_envelope.m_decayTime + m_envelope.m_attackTime){
        modifier = m_envelope.m_maxVolume - ((activeTime - m_envelope.m_attackTime)/m_envelope.m_decayTime * (m_envelope.m_maxVolume - m_envelope.m_sustainVolume));
    }
    else if(timeSecs < m_endTime){
        modifier = m_envelope.m_sustainVolume;
    }
    else{
        modifier = m_envelope.m_sustainVolume - ((timeSecs - m_endTime)/m_envelope.m_releaseTime * m_envelope.m_sustainVolume);
    }
    //V in rare cases, this could stop the note between decay and sustain
    //V however, there is little chance of this happening with doubles
    if(modifier <= 0.0){
        m_isActive = false;
    }
    return m_generator(timeSecs * m_frequency * 6.2831853) * (channel == 1 ? m_right : m_left) * modifier;
}

r8ge::Note::Note(double startTime, short tone, double (*generator)(double), Envelope envelope) : Sound(startTime) {
    m_generator = generator;
    m_frequency = toneToFrequency(tone);
    m_envelope = envelope;
}

r8ge::Note::~Note() = default;

void r8ge::Sound::setEndTime(double endTime) {
    m_endTime = endTime;
}

double r8ge::toneToFrequency(short note){
    return std::pow(2.0, (double)(note - 1)/12) * 27.5;
}

double r8ge::square(double time){
    return std::sin(time) > 0 ? 1.0 : -1.0;
}

void r8ge::Sound::setVolumes(double left, double right) {
    m_left = left;
    m_right = right;
}

bool r8ge::Sound::getState() const {
    return m_isActive;
}

r8ge::Sound::Sound(double startTime) {
    m_startTime = startTime;
    m_isActive = true;
}

void r8ge::Sound::setState(bool state) {
    m_isActive = state;
}

r8ge::Wave::Wave(double startTime, const std::string& filename) : Sound(startTime) {
  // TODO: File<T>  
  Reader::Wave f(filename);
    f.load_wave();
    m_data = f.wave();
    m_endTime = m_startTime + (m_data.m_timeStep * m_data.m_sampleCount);
}

double r8ge::Wave::generate(double timeSecs, unsigned char channel) {
    double activeTime = timeSecs - m_startTime;
    if(activeTime < 0.0 || activeTime > m_endTime){
        return 0;
    }
    channel %= m_data.m_channels;
    double approxIndex = activeTime / m_data.m_timeStep;
    if(approxIndex > m_data.m_sampleCount - 1){
        approxIndex = m_data.m_sampleCount - 1;
    }
    switch (m_data.m_format) {
        case 1:
            switch (m_data.m_blockAlign / m_data.m_channels) {
                case 2:
                    return (double)*((short*)(m_data.m_data) + ((long)approxIndex * m_data.m_channels) + channel) / (1 << 15);
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

r8ge::Wave::~Wave() {
    delete[] m_data.m_data;
}

double r8ge::Wave::getDuration() {
    return m_endTime - m_startTime;
}
