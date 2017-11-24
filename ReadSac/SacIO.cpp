//
// Created by cypress on 24/11/2017.
//
#include <fstream>
#include "SacIO.hpp"

using namespace std;

bool SacIO::readSacHead(const string& sacFile, SacHead& sacHead) {
    ifstream fin (sacFile, ifstream::binary);
    if (!fin.is_open())
        return false;

    char sachead[158*4];

    fin.read(sachead, sizeof(SacHead));
    memcpy(&sacHead, sachead, sizeof(SacHead));

    return true;
}

int SacIO::readSac(const string& sacFile, float* sacData) {
    ifstream fin (sacFile, ifstream::binary);
    if (!fin.is_open())
        return -1;

    fin.seekg(158*4);

    int i = 0;
    auto* buffer = new char [sizeof(float)];

    while (fin.read(buffer, sizeof(float))) {
        memcpy(sacData+i, buffer, sizeof(float));
        i++;
    }

    delete[] buffer;
    return i;
}