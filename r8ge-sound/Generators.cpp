//
// Created by Wiszc on 02.10.2023.
//

#include "Generators.hpp"

// should only output a value
double r8ge::Note::generate(double timeSecs, unsigned char channel) {
    double modifier;
    double activeTime = timeSecs - m_startTime;
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
    if(modifier <= 0.0){
        m_isActive = false;
    }
    return m_generator(timeSecs * m_frequency * 6.2831853) * (channel == 1 ? m_right : m_left) * modifier;
}

r8ge::Note::Note(double startTime, double frequency, double (*generator)(double), Envelope envelope) : Sound(startTime) {
    m_generator = generator;
    m_frequency = frequency;
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


