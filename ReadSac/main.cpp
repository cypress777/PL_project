//
// Created by cypress on 24/11/2017.
//
#include <iostream>
#include <complex>
#include "SacIO.hpp"

using namespace std;

int main (int argc,char **argv) {
    if (argc != 2)
        return -1;

    string sacFile{argv[1]};

    SacIO::SacHead sacHead{};
    if (!SacIO::readSacHead(sacFile, sacHead))
        return -1;

/*    cout << sacHead.kcmpnm << " "<< sacHead.depmin << endl;
    cout << "station name: " << sacHead.kstnm << endl;
    cout << "year: " << sacHead.nzyear << " jday: " << sacHead.nzjday << endl;
    cout << "npts: " << sacHead.npts << endl;
    cout << "location(la, lo): " << sacHead.stla << " " << sacHead.stlo << endl;*/

    auto sacData = new float[sizeof(float)*sacHead.npts];
    int npts = SacIO::readSac(sacFile, sacData);

    if (npts < 0)
        return -1;

//    cout << npts << " points in this sac file" << endl;
    auto fftData = new complex<float>[sizeof(complex<float>)*1024];


    delete[](sacData);
    delete[](fftData);
    return 0;
}