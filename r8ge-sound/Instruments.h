//
// Created by apostrophenome on 24.10.23.
//

#ifndef R8GE_INSTRUMENTS_H
#define R8GE_INSTRUMENTS_H

#include <cmath>

namespace r8ge{

    struct Envelope{
        double m_attackTime = 0.1;
        double m_decayTime = 0.1;
        double m_releaseTime = 0.2;

        double m_sustainVolume = 0.9;
        double m_maxVolume = 1.1;
    };

    struct Instrument{
        Envelope m_envelope{};
        double (*m_generator)(double) = std::sin;
    };

    namespace instruments{

    }
}

#endif //R8GE_INSTRUMENTS_H
