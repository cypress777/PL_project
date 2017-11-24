//
// Created by cypress on 24/11/2017.
//
#include <fstream>
#include <cstring>
#include "SacIO.hpp"

using namespace std;

bool SacIO::readSac(const string& sacFile, float* sacData) {
    char sachead[158*4];

    ifstream fin (sacFile, ifstream::binary);
    if (!fin)
        return false;

    fin.read(sachead, sizeof(SacHead));


    int i = 0;
    auto* buffer = new char [sizeof(float)];

    while (fin.read(buffer, sizeof(float))) {
        memcpy(sacData+i, buffer, sizeof(float));
        cout << sacData[i] << endl;
        i++;
    }

    delete[] buffer;
    return true;
}