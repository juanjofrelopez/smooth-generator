#include <iostream>
#include <cmath>
#include <stdio.h>
#include <chrono>

unsigned int hashy(unsigned int a) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

unsigned int ivalue(int y) {
    return hashy(y<<16)&0xff;
}

float smooth(float x) {
    return 6*x*x*x*x*x - 15*x*x*x*x + 10*x*x*x;
}

float value(float x) {
    int ix = floor(x);
    float fx = smooth(x-ix);
    int v00 = ivalue(ix+0);
    int v01 = ivalue(ix+1);
    float v0 = v00*(1-fx) + v01*fx;
    return v0;
}

int main(){
    int n = 100000;
    uint8_t data[n];

    auto start = std::chrono::high_resolution_clock::now();
    for (int x=0; x<n; x++) {
        float v = 0;

        for (int o=0; o<=4; o++) {
            v += value(x/64.0f*(1<<o))/(1<<o);
        }

        int r = rint(v*0.5f);

        data[x]=r;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<duration.count()<<" microseconds"<<std::endl;

    return 0;
}