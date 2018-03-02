//
// Created by cypress on 24/11/2017.
//
#include <iostream>
#include <complex>
#include "SacToolkit.hpp"


using namespace std;

void testfft() {
    complex<float> fftData[16];
    fftData[0].real(0.5751);
    fftData[1].real(0.4514);
    fftData[2].real(0.0439);
    fftData[3].real(0.0272);
    fftData[4].real(0.3127);
    fftData[5].real(0.0129);
    fftData[6].real(0.3840);
    fftData[7].real(0.6831);
    fftData[8].real(0.0928);
    fftData[9].real(0.0353);
    fftData[10].real(0.6124);
    fftData[11].real (0.6085);
    fftData[12].real (0.0158);
    fftData[13].real (0.0164);
    fftData[14].real (0.1901);
    fftData[15].real (0.5869);

    for (int i = 0; i < 16; i++) {
        cout << fftData[i].real()  << endl;
    }
    cout << "====================" << endl;

    SacToolkit::FFT(fftData, 16);
    for (int i = 0; i < 16; i++) {
        cout << fftData[i].real() << "  " << fftData[i].imag() << endl;
    }
    cout << "====================" << endl;

    SacToolkit::IFFT(fftData, 16);
    for (int i = 0; i < 16; i++) {
        cout << fftData[i].real()  << endl;
    }
}

void testreadsac(string& sacFile) {


    SacToolkit::SacHead sacHead{};
    SacToolkit::ReadSacHead(sacFile, sacHead);

    cout << dec << sacHead.scale << endl;
    cout << "station name: " << sacHead.kstnm << endl;
    cout << "year: " << sacHead.nzyear << " jday: " << sacHead.nzjday << endl;
    cout << "npts: " << sacHead.npts << endl;
    cout << "location(la, lo): " << sacHead.stla << " " << sacHead.stlo << endl;

    auto sacData = new float[sizeof(float)*sacHead.npts];
    int npts = SacToolkit::ReadSac(sacFile, sacData);

    cout << npts << " points in this sac file" << endl;

    for (int i = npts/2; i < npts/2+10; i++) {
        cout << sacData[i] << " ";
    }
    cout << endl;

    float min = sacData[0];
    float max = min;

    for (int i = 1; i < npts; i++) {
        if (sacData[i] < min) min = sacData[i];
        else if (sacData[i] > max) max = sacData[i];
    }

    cout << "min: " << min << endl;
    cout << "max: " << max << endl;

    delete[](sacData);
}

int main (int argc,char **argv) {
    testfft();
    if (argc != 2)
        return -1;

    string sacFile{argv[1]};

    int window = 4096;
    int overlap = 2048;

    SacToolkit::SacHead sacHead{};
    SacToolkit::ReadSacHead(sacFile, sacHead);
    auto sacData = new float[sizeof(float)*sacHead.npts];
    int npts = SacToolkit::ReadSac(sacFile, sacData);

    int winNum = 0;
    while ((++winNum * (window - overlap) + overlap) < npts);

    for (int i = 0; i < winNum; i++) {
        complex<float> fftData[window];
        for (int j = 0; j < window; j++) {
            fftData[j].real(sacData[i * (window-overlap) + j]);
        }

        SacToolkit::FFT(fftData, window);
    }

    return 0;
}