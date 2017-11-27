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
    auto* buffer = new char[sizeof(float)];

    while (fin.read(buffer, sizeof(float))) {
        memcpy(sacData+i, buffer, sizeof(float));
        i++;
    }

    delete[] buffer;
    return i;
}

void SacIO::Dit2(complex<float>* Data,int Log2N,int sign) {
    const float PI = 3.14159;

    int i,j,step,length;
    complex<float> wn,temp,deltawn;
    length=1<<Log2N;
    for(i=0;i<length;i+=2)
    {
        temp=Data[i];
        Data[i]=Data[i]+Data[i+1];
        Data[i+1]=temp-Data[i+1];
    }
    for(i=2;i<=Log2N;i++)
    {
        wn=1;step=1<<i;deltawn=complex<float>((float)cos(2.0*PI/step),(float)sin(sign*2.0*PI/step));
        for(j=0;j<step/2;j++)
        {
            for(i=0;i<length/step;i++)
            {
                temp=Data[i*step+step/2+j]*wn;
                Data[i*step+step/2+j]=Data[i*step+j]-temp;
                Data[i*step+j]=Data[i*step+j]+temp;
            }
            wn=wn*deltawn;
        }
    }
    if(sign==1)
        for(i=0;i<length;i++)
            Data[i]/=length;
}

void SacIO::swap(complex<float>* Data, int i, int j) {
    float t = Data[i].real();
    Data[i].real(Data[j].real());
    Data[j].real(t);

    t = Data[i].imag();
    Data[i].imag(Data[j].imag());
    Data[j].imag(t);
}

void SacIO::BitRev(complex<float>* Data, int Log2N) {
    int pow = 0;
    for (int i = 1; i < Log2N; i *= 2) {
        pow++;
    }

    for (int i = 0; i < Log2N; i++) {
        int a = i;
        int b = 0;

        for (int j = 0; j < pow; j++) {
            b = (b << 1) + (a & 1); // b = b * 2 + a % 2;
            a >>= 1; // a = a/2;]
        }

        if (b > i)
            swap(Data, b, i);
    }
}

void SacIO::FFT(complex<float>* Data, int Log2N) {
    const float PI = 3.14159;
    float tReal = cos(-2 * PI / Log2N);
    float tImag = sin(-2 * PI / Log2N);

    BitRev(Data, Log2N);

    complex<float> W[Log2N/2];
    W[0].real(1);
    W[0].imag(0);

    for (int i = 1; i < Log2N/2; i++) {
        W[i].real(W[i - 1].real() * tReal - W[i - 1].imag() * tImag);
        W[i].real(W[i - 1].real() * tImag + W[i - 1].imag() * tReal);
    }

    for (int i = 2; i <= Log2N; i *= 2)
    {
        for (int j = 0; j < Log2N; j += i)
        {
            for (int k = 0; k < i / 2;  k++)
            {
                int index1 = j + k;
                int index2 = index1 + i / 2;
                int t = Log2N * k / i;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
                tReal = W[t].real() * Data[index2].real() - W[t].imag() * Data[index2].imag();
                tImag = W[t].real() * Data[index2].imag() - W[t].imag() * Data[index2].real();
                float ureal = Data[index1].real();
                float uimag = Data[index1].imag();
                Data[index1].real(ureal + tReal);
                Data[index1].imag(uimag + tImag);
                Data[index2].real(ureal - tReal);
                Data[index2].imag(uimag - tImag);
            }
        }
    }
}