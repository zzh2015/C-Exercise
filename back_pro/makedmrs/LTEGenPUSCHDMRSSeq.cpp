#include "LTEGenPUSCHDMRSSeq.h"

#include <math.h>
#include <memory.h>
#include <stdio.h>

#include "LTEGenPNSeq.h"
#include "Complex.h"

LTEGenPUSCHDMRSSeq::LTEGenPUSCHDMRSSeq()
{
}

/**
 * @brief LTEGenPUSCHDMRSSeq::GenetatePUSCHDMRSSeq
 * @param dmrsSeqConfig
 * @param DMRSSeq
 * @return
 */
int LTEGenPUSCHDMRSSeq::GenetatePUSCHDMRSSeq(DMRSSeqConfig *dmrsSeqConfig, Complex DMRSSeq[][1200])
{
    int retValue = 0;
    if (!dmrsSeqConfig->m_SeqHoppingEnabled) {
        LTEGenPNSeq PNGenerator;
        int v = 0;

        int primeList[] = {0, 11, 23, 31, 47, 59, 71, 83, 89, 107, 113, 131, 139, 151, 167,
                           179, 191, 199, 211, 227, 239, 251, 263, 271, 283, 293, 311, 317, 331, 347,
                           359, 367, 383, 389, 401, 419, 431, 443, 449, 467, 479, 491, 503, 509, 523,
                           523, 547, 563, 571, 587, 599, 607, 619, 631, 647, 659, 661, 683, 691, 701,
                           719, 727, 743, 751, 761, 773, 787, 797, 811, 827, 839, 839, 863, 863, 887,
                           887, 911, 919, 929, 947, 953, 971, 983, 991, 997, 1019, 1031, 1039, 1051, 1063,
                           1069, 1091, 1103, 1109, 1123, 1129, 1151, 1163, 1171, 1187, 1193};

        int M_RS_sc = dmrsSeqConfig->m_LengthPRB * 12;
        int N_RS_ZC = primeList[dmrsSeqConfig->m_LengthPRB];    //get max prime

        printf("N_RS_ZC: %d\n", N_RS_ZC);

        unsigned char DMRS_1[] = {0, 2, 3, 4, 6, 8, 9, 10};
        unsigned char DMRS_2[] = {0, 6, 3, 4, 2, 8, 10, 9};

        unsigned char n_DMRS_1 = DMRS_1[dmrsSeqConfig->m_CyclicShiftHighLayer];
        unsigned char n_DMRS_2 = DMRS_2[dmrsSeqConfig->m_CyclicShiftHighLayerDCI0];

        //2 slot
        for (int j=0; j!=2; ++j) {
            int n_s;

            if (0 == j) {
                n_s = dmrsSeqConfig->m_IndexCurrentSubframe * 2;
            } else if (1 == j) {
                n_s = dmrsSeqConfig->m_IndexCurrentSubframe * 2 + 1;
            }

            int f_gh = 0;
            if (dmrsSeqConfig->m_GroupHoppingEnabled) {
                int c_init_gh = dmrsSeqConfig->m_CellID / 30; //floor
                int n_s_max = 20;
                int max_c_index = 8 * n_s_max + 8;
                char c_gh[8400];
                PNGenerator.MakeSequence(max_c_index, c_init_gh, c_gh);

                int sumTemp = 0;
                for (int i=0; i!=8; ++i) {
                    sumTemp += c_gh[8*n_s+i] * pow(2, i);
                }
                f_gh = sumTemp % 30;
            } else {
                f_gh = 0;
            }

            int fss_PUCCH = dmrsSeqConfig->m_CellID % 30;
            int fss_PUSCH = (fss_PUCCH+dmrsSeqConfig->m_GroupAssignmentPUSCH) % 30;
            int u = (f_gh+fss_PUSCH) % 30;

            int c_init = (dmrsSeqConfig->m_CellID/30)*32 + fss_PUSCH;
            int N_UL_symb = 7;
            int n_s_max = 20;

            int max_c_index = 8 * N_UL_symb * n_s_max + 8;
            char c[8400];

            PNGenerator.MakeSequence(max_c_index, c_init, c);

            double q_bar = 1.0 * N_RS_ZC * (u+1) / 31;  //double
            int q = floor(q_bar+0.5) + v*pow(-1, floor(2*q_bar));

            printf(" the value of q_bar: %lf, the value of q: %d\n", q_bar, q);

            int n_PN = 0;
            for (int i=0; i!=8; ++i) {
                n_PN += c[8*N_UL_symb*n_s+i] * pow(2, i);
            }
            int n_CS = (n_DMRS_1+n_DMRS_2+n_PN) % 12;
            float alpha = (2 * M_PI * n_CS) / 12;

            printf(" the value of alpha: %f\n", alpha);

            if (1 == dmrsSeqConfig->m_LengthPRB) {
                char phi_1[][12] = {
                    { -1,	1,	3,	-3,	3,	3,	1,	1,	3,	1,	-3,	3 },
                    { 1,	1,	3,	3,	3,	-1,	1,	-3,	-3,	1,	-3,	3 },
                    { 1,	1,	-3,	-3,	-3,	-1,	-3,	-3,	1,	-3,	1,	-1 },
                    { -1,	1,	1,	1,	1,	-1,	-3,	-3,	1,	-3,	3,	-1 },
                    { -1,	3,	1,	-1,	1,	-1,	-3,	-1,	1,	-1,	1,	3 },
                    { 1,	-3,	3,	-1,	-1,	1,	1,	-1,	-1,	3,	-3,	1 },
                    { -1,	3,	-3,	-3,	-3,	3,	1,	-1,	3,	3,	-3,	1 },
                    { -3,	-1,	-1,	-1,	1,	-3,	3,	-1,	1,	-3,	3,	1 },
                    { 1,	-3,	3,	1,	-1,	-1,	-1,	1,	1,	3,	-1,	1 },
                    { 1,	-3,	-1,	3,	3,	-1,	-3,	1,	1,	1,	1,	1 },
                    { -1,	3,	-1,	1,	1,	-3,	-3,	-1,	-3,	-3,	3,	-1 },
                    { 3,	1,	-1,	-1,	3,	3,	-3,	1,	3,	1,	3,	3 },
                    { 1,	-3,	1,	1,	-3,	1,	1,	1,	-3,	-3,	-3,	1 },
                    { 3,	3,	-3,	3,	-3,	1,	1,	3,	-1,	-3,	3,	3 },
                    { -3,	1,	-1,	-3,	-1,	3,	1,	3,	3,	3,	-1,	1 },
                    { 3,	-1,	1,	-3,	-1,	-1,	1,	1,	3,	1,	-1,	-3 },
                    { 1,	3,	1,	-1,	1,	3,	3,	3,	-1,	-1,	3,	-1 },
                    { -3,	1,	1,	3,	-3,	3,	-3,	-3,	3,	1,	3,	-1 },
                    { -3,	3,	1,	1,	-3,	1,	-3,	-3,	-1,	-1,	1,	-3 },
                    { -1,	3,	1,	3,	1,	-1,	-1,	3,	-3,	-1,	-3,	-1 },
                    { -1,	-3,	1,	1,	1,	1,	3,	1,	-1,	1,	-3,	-1 },
                    { -1,	3,	-1,	1,	-3,	-3,	-3,	-3,	-3,	1,	-1,	-3 },
                    { 1,	1,	-3,	-3,	-3,	-3,	-1,	3,	-3,	1,	-3,	3 },
                    { 1,	1,	-1,	-3,	-1,	-3,	1,	-1,	1,	3,	-1,	1 },
                    { 1,	1,	3,	1,	3,	3,	-1,	1,	-1,	-3,	-3,	1 },
                    { 1,	-3,	3,	3,	1,	3,	3,	1,	-3,	-1,	-1,	3 },
                    { 1,	3,	-3,	-3,	3,	-3,	1,	-1,	-1,	3,	-1,	-3 },
                    { -3,	-1,	-3,	-1,	-3,	3,	1,	-1,	1,	3,	-3,	-3 },
                    { -1,	3,	-3,	3,	-1,	3,	3,	-3,	3,	3,	-1,	-1 },
                    { 3,	-3,	-3,	-1,	-1,	-3,	-1,	3,	-3,	3,	1,	-1}
                };
                Complex r_alpha[12];

                for (int n=0; n!=12; ++n) {
                    r_alpha[n].m_real = cos(alpha*n + phi_1[u][n]*M_PI/4);
                    r_alpha[n].m_imag = sin(alpha*n + phi_1[u][n]*M_PI/4);
                }
                if (0 == j) {
                    memcpy(DMRSSeq[0], r_alpha, 12*sizeof(Complex));
                } else if (1 == j){
                    memcpy(DMRSSeq[1], r_alpha, 12*sizeof(Complex));
                }
                retValue = 12;
            } else if (2 == dmrsSeqConfig->m_LengthPRB) {
                char phi_2[][24] = {
                    { -1,	3,	1,	-3,	3,	-1,	1,	3,	-3,	3,	1,	3,	-3,	3,	1,	1,	-1,	1,	3,	-3,	3,	-3,	-1,	-3 },
                    { -3,	3,	-3,	-3,	-3,	1,	-3,	-3,	3,	-1,	1,	1,	1,	3,	1,	-1,	3,	-3,	-3,	1,	3,	1,	1,	-3 },
                    { 3,	-1,	3,	3,	1,	1,	-3,	3,	3,	3,	3,	1,	-1,	3,	-1,	1,	1,	-1,	-3,	-1,	-1,	1,	3,	3 },
                    { -1,	-3,	1,	1,	3,	-3,	1,	1,	-3,	-1,	-1,	1,	3,	1,	3,	1,	-1,	3,	1,	1,	-3,	-1,	-3,	-1 },
                    { -1,	-1,	-1,	-3,	-3,	-1,	1,	1,	3,	3,	-1,	3,	-1,	1,	-1,	-3,	1,	-1,	-3,	-3,	1,	-3,	-1,	-1 },
                    { -3,	1,	1,	3,	-1,	1,	3,	1,	-3,	1,	-3,	1,	1,	-1,	-1,	3,	-1,	-3,	3,	-3,	-3,	-3,	1,	1 },
                    { 1,	1,	-1,	-1,	3,	-3,	-3,	3,	-3,	1,	-1,	-1,	1,	-1,	1,	1,	-1,	-3,	-1,	1,	-1,	3,	-1,	-3 },
                    { -3,	3,	3,	-1,	-1,	-3,	-1,	3,	1,	3,	1,	3,	1,	1,	-1,	3,	1,	-1,	1,	3,	-3,	-1,	-1,	1 },
                    { -3,	1,	3,	-3,	1,	-1,	-3,	3,	-3,	3,	-1,	-1,	-1,	-1,	1,	-3,	-3,	-3,	1,	-3,	-3,	-3,	1,	-3 },
                    { 1,	1,	-3,	3,	3,	-1,	-3,	-1,	3,	-3,	3,	3,	3,	-1,	1,	1,	-3,	1,	-1,	1,	1,	-3,	1,	1 },
                    { -1,	1,	-3,	-3,	3,	-1,	3,	-1,	-1,	-3,	-3,	-3,	-1,	-3,	-3,	1,	-1,	1,	3,	3,	-1,	1,	-1,	3 },
                    { 1,	3,	3,	-3,	-3,	1,	3,	1,	-1,	-3,	-3,	-3,	3,	3,	-3,	3,	3,	-1,	-3,	3,	-1,	1,	-3,	1 },
                    { 1,	3,	3,	1,	1,	1,	-1,	-1,	1,	-3,	3,	-1,	1,	1,	-3,	3,	3,	-1,	-3,	3,	-3,	-1,	-3,	-1 },
                    { 3,	-1,	-1,	-1,	-1,	-3,	-1,	3,	3,	1,	-1,	1,	3,	3,	3,	-1,	1,	1,	-3,	1,	3,	-1,	-3,	3 },
                    { -3,	-3,	3,	1,	3,	1,	-3,	3,	1,	3,	1,	1,	3,	3,	-1,	-1,	-3,	1,	-3,	-1,	3,	1,	1,	3 },
                    { -1,	-1,	1,	-3,	1,	3,	-3,	1,	-1,	-3,	-1,	3,	1,	3,	1,	-1,	-3,	-3,	-1,	-1,	-3,	-3,	-3,	-1 },
                    { -1,	-3,	3,	-1,	-1,	-1,	-1,	1,	1,	-3,	3,	1,	3,	3,	1,	-1,	1,	-3,	1,	-3,	1,	1,	-3,	-1 },
                    { 1,	3,	-1,	3,	3,	-1,	-3,	1,	-1,	-3,	3,	3,	3,	-1,	1,	1,	3,	-1,	-3,	-1,	3,	-1,	-1,	-1 },
                    { 1,	1,	1,	1,	1,	-1,	3,	-1,	-3,	1,	1,	3,	-3,	1,	-3,	-1,	1,	1,	-3,	-3,	3,	1,	1,	-3 },
                    { 1,	3,	3,	1,	-1,	-3,	3,	-1,	3,	3,	3,	-3,	1,	-1,	1,	-1,	-3,	-1,	1,	3,	-1,	3,	-3,	-3 },
                    { -1,	-3,	3,	-3,	-3,	-3,	-1,	-1,	-3,	-1,	-3,	3,	1,	3,	-3,	-1,	3,	-1,	1,	-1,	3,	-3,	1,	-1 },
                    { -3,	-3,	1,	1,	-1,	1,	-1,	1,	-1,	3,	1,	-3,	-1,	1,	-1,	1,	-1,	-1,	3,	3,	-3,	-1,	1,	-3 },
                    { -3, -1, -3,	3,	1,	-1,	-3,	-1,	-3,	-3,	3,	-3,	3,	-3,	-1,	1,	3,	1,	-3,	1,	3,	3,	-1,	-3 },
                    { -1,	-1,	-1,	-1,	3,	3,	3,	1,	3,	3,	-3,	1,	3,	-1,	3,	-1,	3,	3,	-3,	3,	1,	-1,	3,	3 },
                    { 1,	-1,	3,	3,	-1,	-3,	3,	-3,	-1,	-1,	3,	-1,	3,	-1,	-1,	1,	1,	1,	1,	-1,	-1,	-3,	-1,	3 },
                    { 1,	-1,	1,	-1,	3,	-1,	3,	1,	1,	-1,	-1,	-3,	1,	1,	-3,	1,	3,	-3,	1,	1,	-3,	-3,	-1,	-1 },
                    { -3,	-1,	1,	3,	1,	1,	-3,	-1,	-1,	-3,	3,	-3,	3,	1,	-3,	3,	-3,	1,	-1,	1,	-3,	1,	1,	1 },
                    { -1,	-3,	3,	3,	1,	1,	3,	-1,	-3,	-1,	-1,	-1,	3,	1,	-3,	-3,	-1,	3,	-3,	-1,	-3,	-1,	-3,	-1 },
                    { -1,	-3,	-1,	-1,	1,	-3,	-1,	-1,	1,	-1,	-3,	1,	1,	-3,	1,	-3,	-3,	3,	1,	1,	-1,	3,	-1,	-1 },
                    { 1,	1,	-1,	-1,	-3,	-1,	3,	-1,	3,	-1,	1,	3,	1,	-1,	3,	1,	3,	-3,	-3,	1,	-1,	-1,	1,	3}
                };
                Complex r_alpha[24];

                for (int n=0; n!=24; ++n) {
                    r_alpha[n].m_real = cos(alpha*n + phi_2[u][n]*M_PI/4);
                    r_alpha[n].m_imag = sin(alpha*n + phi_2[u][n]*M_PI/4);
//                    printf("no:%d m_real=%f, m_imag=%f\n", n, r_alpha[n].m_real, r_alpha[n].m_imag);
                }
                if (0 == j) {
                    memcpy(DMRSSeq[0], r_alpha, 24*sizeof(Complex));
                } else if (1 == j){
                    memcpy(DMRSSeq[1], r_alpha, 24*sizeof(Complex));
                }
                retValue = 24;
            } else {    //length_PRB > 2
                Complex r_alpha[1200];
                int m  = 0;
                for (int n=0; n!=M_RS_sc; ++n) {
                    m = n % N_RS_ZC;
                    r_alpha[n].m_real = cos(alpha*n - (M_PI*q*m*(m+1)/N_RS_ZC));
                    r_alpha[n].m_imag = sin(alpha*n - (M_PI*q*m*(m+1)/N_RS_ZC));
                }
                if (0 == j) {
                    memcpy(DMRSSeq[0], r_alpha, M_RS_sc*sizeof(Complex));
                } else if (1 == j){
                    memcpy(DMRSSeq[1], r_alpha, M_RS_sc*sizeof(Complex));
                }
                retValue = M_RS_sc;
            }
        }
    } else {
        printf("not code yet for sequence hopping\n");
        retValue = 0;
    }

    return retValue;
}

