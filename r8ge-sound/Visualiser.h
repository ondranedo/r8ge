//
// Created by apostrophenome on 21.10.23.
//

#ifndef R8GE_VISUALISER_H
#define R8GE_VISUALISER_H

#include <complex>
#include <valarray>

namespace r8ge{
    void simpleFastFourier(std::valarray<std::complex<float>> arr);
    void fft(float* out, float* in, int count);
}

#endif //R8GE_VISUALISER_H
