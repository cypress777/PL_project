//
// Created by cypress on 24/11/2017.
//
#include <iostream>
#include "SacIO.hpp"
#define nmax 400000

using namespace std;

int main (int argc,char **argv) {
    if (argc != 2)
        return -1;

    string sacFile{argv[1]};

    float sacData[nmax];
    SacIO::SacHead sacHead{};

    if (!SacIO::readSacHead(sacFile, sacHead))
        return -1;

    cout << sacHead.scale << endl;
    cout << "station name: " << sacHead.kstnm << endl;
    cout << "year: " << sacHead.nzyear << " jday: " << sacHead.nzjday << endl;
    cout << "npts: " << sacHead.npts << endl;
    cout << "location(la, lo): " << sacHead.stla << " " << sacHead.stlo << endl;

    int npts = SacIO::readSac(sacFile, sacData);
    if (npts < 0)
        return -1;

    cout << npts << " points in this sac file" << endl;

    return 0;
}