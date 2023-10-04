//
// Created by Wiszc on 02.10.2023.
//

#include "Generators.hpp"

// should only output a value
double r8ge::Note::generate(double timeSecs, unsigned char channel) {
    return m_generator(timeSecs * m_frequency * 6.2831853) * (channel == 1 ? m_right : m_left);
}

void r8ge::Note::setGenerator(double (*generator)(double)) {
    m_generator = generator;
}

void r8ge::Note::setFrequency(double freq) {
    m_frequency = freq;
}

r8ge::Note::~Note() = default;

double r8ge::Sound::getEndTime() const {
    return m_endTime;
}

void r8ge::Sound::setEndTime(double mEndTime) {
    m_endTime = mEndTime;
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

r8ge::Sound::~Sound() = default;

