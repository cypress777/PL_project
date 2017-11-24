//
// Created by cypress on 24/11/2017.
//
#include <iostream>
#include "SacIO.hpp"
#define nmax 870000

using namespace std;

int main () {
    float sacData[nmax];
    if (!SacIO::readSac("2016_200_20_G_TAM_BHZ.SAC", sacData))
        return -1;

    return 0;
}