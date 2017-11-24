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
    if (!fin.is_open())
        return false;

    fin.read(sachead, sizeof(SacHead));


    int i = 0;

    while (fin >> sacData[i]) {
        cout << sacData[i] << endl;
        i++;
    }
    
    return true;
}