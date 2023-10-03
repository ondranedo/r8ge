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
