#include "Double2Complex.h"
#include <emmintrin.h>
#include <immintrin.h>

#define SET_1 (0x1<<31)

void DoubleToComplex(double *srcI, double *srcQ, Complex *dst, const unsigned int len)
{
    __m256d avxR_D, avxI_D, avxX_D, avxY_D, avxA_D, avxB_D;
    __m128 avxA, avxB;
#if 1
    __m256 avxD;
#endif
    for (unsigned int i=0; i+4<=len; i+=4) {
        avxR_D = _mm256_loadu_pd(srcI + i);
        avxI_D = _mm256_loadu_pd(srcQ + i);
        avxX_D = _mm256_unpacklo_pd(avxR_D, avxI_D); //swizzle
        avxY_D = _mm256_unpackhi_pd(avxR_D, avxI_D);
        avxA_D = _mm256_permute2f128_pd(avxX_D, avxY_D, 0x20);
        avxB_D = _mm256_permute2f128_pd(avxX_D, avxY_D, 0x31);
        avxA = _mm256_cvtpd_ps(avxA_D); //double to float
        avxB = _mm256_cvtpd_ps(avxB_D);
#if 0
        avxD = _mm256_castps128_ps256(avxA); 
        avxD = _mm256_insertf128_ps(avxD, avxB, 1);
        _mm256_storeu_ps((float*)(dst+i), avxD);
#else
        _mm_maskstore_ps((float*)(dst+i), _mm_set_epi32(SET_1, SET_1, SET_1, SET_1), avxA);
        _mm_maskstore_ps((float*)(dst+i+2), _mm_set_epi32(SET_1, SET_1, SET_1, SET_1), avxB);
#endif
    }

    for (unsigned int i=len-(len & 0x03); i<len; ++i) {
        dst[i].m_real = static_cast<float>(srcI[i]);
        dst[i].m_imag = static_cast<float>(srcQ[i]);
    }
}

void ComplexToDouble(Complex *src, double *dstI, double *dstQ, const unsigned int len)
{
    __m128 avxA, avxB;
    __m256d avxA_D, avxB_D, avxX_D, avxY_D, avxR_D, avxI_D;
    for (unsigned int i=0; i+4<=len; i+=4) {
        avxA = _mm_maskload_ps((float*)(src+i), _mm_set_epi32(SET_1, SET_1, SET_1, SET_1)); //load float
        avxB = _mm_maskload_ps((float*)(src+i+2), _mm_set_epi32(SET_1, SET_1, SET_1, SET_1));
        avxA_D = _mm256_cvtps_pd(avxA); //float to double
        avxB_D = _mm256_cvtps_pd(avxB);
        avxX_D = _mm256_permute2f128_pd(avxA_D, avxB_D, 0x20);
        avxY_D = _mm256_permute2f128_pd(avxA_D, avxB_D, 0x31);
        avxR_D = _mm256_shuffle_pd(avxX_D, avxY_D, 0x00);
        avxI_D = _mm256_shuffle_pd(avxX_D, avxY_D, 0x0f);
        _mm256_storeu_pd(dstI+i, avxR_D);   //store
        _mm256_storeu_pd(dstQ+i, avxI_D);
    }

    for (unsigned int i=len-(len&0x03); i<len; ++i) {
        dstI[i] = static_cast<double>(src[i].m_real);
        dstQ[i] = static_cast<double>(src[i].m_imag);
    }
}

