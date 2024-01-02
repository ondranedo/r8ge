//
// Created by apostrophenome on 21.10.23.
//

#include "Visualiser.h"

using namespace std::complex_literals;

void r8ge::fft(float *out, float *in, int count){

    int k = 0;
    std::valarray<std::complex<float>> arr(count);
    for(auto& n : arr){
        n = in[k++];
    }
    simpleFastFourier(arr);
    k = 0;
    for(auto& n : arr){
        out[k++] = std::abs(n);
    }
}

void r8ge::simpleFastFourier(std::valarray<std::complex<float>> arr) {
    int count = arr.size();

    if(count == 1){
        return;
    }

    std::valarray<std::complex<float>> odd = arr[std::slice(1, count >> 1, 2)];
    std::valarray<std::complex<float>> even = arr[std::slice(0, count >> 1, 2)];

    simpleFastFourier(odd);
    simpleFastFourier(even);

    std::complex<float> t;
    for(int k = 0; k < count >> 1; k++){
        t = (std::complex<float>)std::polar(1.0, -2 * 3.141592653589793238462 * k / count) * odd[k];
        arr[k] = even[k] + t;
        arr[k + (count >> 1)] = even[k] - t;
    }
}

void r8ge::printVisualiser(AudioPusher& audio){
    const int barsCount = 10;
    double sampleStep = 1.0 / R8GE_LAST_SAMPLE_COUNT;
    double barsStep = 1.0 / barsCount;

    auto transformed = new float[R8GE_LAST_SAMPLE_COUNT];
    while(1){
        fft(transformed, audio.newCurrentSamples(), R8GE_LAST_SAMPLE_COUNT);

        for(int i = 0; i < barsCount; i++){
            for(int j = 0; (sampleStep * j) < (barsStep * i); j++){

            }
        }
    }
}