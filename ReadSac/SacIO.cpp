//
// Created by cypress on 24/11/2017.
//
#include <cstdio>
#include "SacIO.hpp"

using namespace std;

bool SacIO::readSac(const string& sacFile, float* sacData) {
    FILE *fp;
    char sachead[158*4];

    fp = fopen(sacFile.c_str(), "rb");
    if (fp == nullptr)
        return false;

    fscanf(fp, "%s", sachead);
    fseek(fp, 158*4, 0);

    int i = 0;
    while (fscanf(fp, "%f", &sacData[i])) {
        cout << sacData[i] << endl;
        i++;
    }

    return true;
}