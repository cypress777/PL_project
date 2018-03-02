//
// Created by cypress on 01/03/2018.
//

#include <iostream>
#include <complex>
#include "SacToolkit.hpp"

int main (int argc, char** argv) {
    if (argc != 4)
        return -1;

    string sacFile = string(argv[1]);
    int window = stoi(string(argv[2]));
    int overlap = stoi(string(argv[3]));

    cout << window << " " << overlap;

    SacToolkit::SacHead sacHead{0};
    if (!SacToolkit::ReadSacHead(sacFile, sacHead))
        return -1;
    
    auto sacData = new float[sizeof(float)*sacHead.npts];
    if (sacHead.npts != SacToolkit::ReadSac(sacFile, sacData))
        cout << "the actual npts in Sac does not match with sacHead";

    int sacSeg = 0;
    while ((++sacSeg * (window - overlap) + overlap) < sacHead.npts);

    for (int i = 0; i < sacSeg; i++) {
        complex<float> fftData[window];
        for (int j = 0; j < window; j++) {
            fftData[j].real(sacData[i * (window-overlap) + j]);
        }

        SacToolkit::FFT(fftData, window);

    }

    return 1;
}