//
// Created by cypress on 24/11/2017.
//
#include <iostream>
#include <complex>
#include "SacIO.hpp"

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

    SacIO::FFT(fftData, 16);
    for (int i = 0; i < 16; i++) {
        cout << fftData[i].real() << "  " << fftData[i].imag() << endl;
    }
    cout << "====================" << endl;

    SacIO::IFFT(fftData, 16);
    for (int i = 0; i < 16; i++) {
        cout << fftData[i].real()  << endl;
    }
}

void testreadsac(string& sacFile) {


    SacIO::SacHead sacHead{};
    SacIO::readSacHead(sacFile, sacHead);

    cout << sacHead.kcmpnm << " "<< sacHead.depmin << endl;
    cout << "station name: " << sacHead.kstnm << endl;
    cout << "year: " << sacHead.nzyear << " jday: " << sacHead.nzjday << endl;
    cout << "npts: " << sacHead.npts << endl;
    cout << "location(la, lo): " << sacHead.stla << " " << sacHead.stlo << endl;

    auto sacData = new float[sizeof(float)*sacHead.npts];
    int npts = SacIO::readSac(sacFile, sacData);

    cout << npts << " points in this sac file" << endl;

    delete[](sacData);
}

int main (int argc,char **argv) {
    if (argc != 2)
        return -1;

    string sacFile{argv[1]};

    testreadsac(sacFile);

//    testfft();
    return 0;
}