#include <stdio.h>
#include <sys/time.h>

#include "Double2Complex.h"

int main(void)
{
#define N 10
#if 0
    double src1[N] = {0.00};//{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09};
    double src2[N] = {-0.00};//{-0.01, -0.02, -0.03, -0.04, -0.05, -0.06, -0.07, -0.08, -0.09};

    Complex *c = new Complex[N];
    Complex *cc = new Complex[N];
#endif

   double src1[10] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 1.00};
   double src2[10] = {-0.1, -0.2, -0.03, -0.04, -0.05, -0.06, -0.07, -0.08, -0.09, -1.00};

   Complex *c = new Complex[10];
   Complex *cc = new Complex[10];


    struct timeval start_fun, end_fun, start_d, end_d;

    gettimeofday(&start_fun, NULL);
    for (int i=0; i<10000; ++i)
    DoubleToComplex(src1, src2, c, N);
    gettimeofday(&end_fun, NULL);

    gettimeofday(&start_d, NULL);
    for (int j=0; j<10000; ++j)
    for (int i=0; i!=N; ++i) {
        cc[i].m_real = static_cast<float>(src1[i]);
        cc[i].m_imag = static_cast<float>(src2[i]);
    }
    gettimeofday(&end_d, NULL);

    printf("func performance time:%ld\n", ((end_fun.tv_sec*1000000+end_fun.tv_usec)
                - (start_fun.tv_sec*1000000+start_fun.tv_usec)));
    printf("dirc trans time:%ld\n", ((end_d.tv_sec*1000000+end_d.tv_usec)
                - (start_d.tv_sec*1000000+start_d.tv_usec)));
#if 1
    for (int i=0; i!=10; ++i) {
        printf("func no %d real=%f,imag=%f\n", i, c[i].m_real, c[i].m_imag);
        printf("dirc no %d real=%f,imag=%f\n", i, cc[i].m_real, cc[i].m_imag);
    }
#endif

#if 1
    double dstR[8];
    double dstI[8];
    ComplexToDouble(cc, dstR, dstI, 8);
    for (int i=0; i!=8; ++i) {
        printf("<real=%lf,imag=%lf>\n", dstR[i], dstI[i]);
    }
#endif

    return 0;
}

