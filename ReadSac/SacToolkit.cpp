//
// Created by cypress on 24/11/2017.
//
#include <fstream>
#include "SacToolkit.hpp"

using namespace std;

bool SacToolkit::ReadSacHead(const string& sacFile, SacHead & sacHead) {
    ifstream fin (sacFile, ifstream::binary);
    if (!fin.is_open())
        return false;

    char sachead[158*4];

    fin.read(sachead, sizeof(SacHead));
    memcpy(&sacHead, sachead, sizeof(SacHead));

    return true;
}

int SacToolkit::ReadSac(const string& sacFile, float* sacData) {
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

void SacToolkit::Swap(complex<float>* Data, int i, int j) {
    float t = Data[i].real();
    Data[i].real(Data[j].real());
    Data[j].real(t);

    t = Data[i].imag();
    Data[i].imag(Data[j].imag());
    Data[j].imag(t);
}

void SacToolkit::BitRev(complex<float>* Data, int Log2N) {
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
            Swap(Data, b, i);
    }
}

void SacToolkit::FFT(complex<float>* Data, int Log2N) {
    const float PI = 3.14159;
    float tReal = cos(-2 * PI / Log2N);
    float tImag = sin(-2 * PI / Log2N);

    BitRev(Data, Log2N);

    complex<float> W[Log2N/2];
    W[0].real(1);
    W[0].imag(0);

    for (int i = 1; i < Log2N/2; i++) {
        W[i].real(W[i - 1].real() * tReal - W[i - 1].imag() * tImag);
        W[i].imag(W[i - 1].real() * tImag + W[i - 1].imag() * tReal);
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
                tImag = W[t].real() * Data[index2].imag() + W[t].imag() * Data[index2].real();
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

void SacToolkit::IFFT(complex<float>* Data, int Log2N) {
    const float PI = 3.14159;
    float tReal = cos(2 * PI / Log2N);
    float tImag = sin(2 * PI / Log2N);

    BitRev(Data, Log2N);

    complex<float> W[Log2N/2];
    W[0].real(1);
    W[0].imag(0);

    for (int i = 1; i < Log2N/2; i++) {
        W[i].real(W[i - 1].real() * tReal - W[i - 1].imag() * tImag);
        W[i].imag(W[i - 1].real() * tImag + W[i - 1].imag() * tReal);
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
                tImag = W[t].real() * Data[index2].imag() + W[t].imag() * Data[index2].real();
                float ureal = Data[index1].real();
                float uimag = Data[index1].imag();
                Data[index1].real(ureal + tReal);
                Data[index1].imag(uimag + tImag);
                Data[index2].real(ureal - tReal);
                Data[index2].imag(uimag - tImag);
            }
        }
    }

    for (int i = 0; i < Log2N; i++)
    {
        float t = Data[i].real() / Log2N;
        Data[i].real(t);
        t = Data[i].imag() / Log2N;
        Data[i].imag(t);
    }
}
