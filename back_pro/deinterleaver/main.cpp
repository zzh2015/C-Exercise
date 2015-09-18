#include <iostream>

#include "LTEULSCHDeinterleaver.h"

using namespace std;

int main(void)
{
    PUSCHBetaIndex bi = {0, 0, 0};
    ControlInfoBits cib = {0, 0, 0};
    float input[14400] = {0.0f};
    float output[14400];
    LTEULSCHDeinterleaver *d = new LTEULSCHDeinterleaver(bi, cib, 0, true, 0, 0, input);

    int len = d->Deinterleaver(output);

    cout << "Test LTEULSCHDeinterleave" << endl;

    return 0;
}

