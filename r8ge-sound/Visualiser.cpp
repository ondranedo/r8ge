//
// Created by apostrophenome on 21.10.23.
//

#include "Visualiser.h"
#include <cmath>
#include <complex>

using namespace std::complex_literals;

void r8ge::simpleFastFourier(float *out, float *in, int count, int stride) {
    // assigning final value
    if(count == 1){
        *out = *in;
    }
    else{
        // finding odd and even values in subarrays
        simpleFastFourier(out, in, count >> 1, stride << 1);
        simpleFastFourier(out + (count >> 1), in + stride ,count >> 1, stride << 1);
        // magic idk
        for(int k = 0; k < count >> 1; k++){
            float p = out[k];
            float q = (std::exp(((-2 * 3.14159 * 1i) /= count) *= k).real() * out[k + (count >> 1)]);
            out[k] = p + q;
            out[k + (count >> 1)] = p - q;
        }
    }
}