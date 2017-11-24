//
// Created by cypress on 24/11/2017.
//
#include <fstream>
#include "SacIO.hpp"

using namespace std;

bool SacIO::readSac(const string& sacFile, float* sacData) {
    char sachead[158*4];
    SacHead sacHead;

    ifstream fin (sacFile, ifstream::binary);
    if (!fin.is_open())
        return false;

    fin.read(sachead, sizeof(SacHead));
    memcpy(&sacHead, sachead, sizeof(SacHead));

    cout << "station name: " << sacHead.kstnm << endl;
    cout << "npts: " << sacHead.npts << endl;
    cout << "location(la, lo): " << sacHead.stla << " " << sacHead.stlo << endl;

    int i = 0;
    auto* buffer = new char [sizeof(float)];

    while (fin.read(buffer, sizeof(float))) {
        memcpy(sacData+i, buffer, sizeof(float));
        i++;
    }

    cout << i << " points" << endl;

    delete[] buffer;
    return true;
}