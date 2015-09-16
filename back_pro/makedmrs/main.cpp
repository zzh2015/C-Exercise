#include "LTEGenPUSCHDMRSSeq.h"

#include <stdio.h>

#include "Complex.h"

int main()
{
    LTEGenPUSCHDMRSSeq dmrsSeqGenerator;
    Complex DMRSSeq[2][1200];
    int d = 0;

    DMRSSeqConfig m_DMRSSeqConfig = {200, 2, 25, false, true, 15, 5, 0};

    d = dmrsSeqGenerator.GenetatePUSCHDMRSSeq(&m_DMRSSeqConfig, DMRSSeq);

#if 1
    FILE *fp_r = NULL;
    FILE *fp_i = NULL;
    
    float real[601] = {0};
    float imag[601] = {0};

    fp_r = fopen("dmrs_r.dat", "r");
    fp_i = fopen("dmrs_i.dat", "r");

    if ((NULL == fp_r) || (NULL == fp_i)) {
        printf("open error!\n");
    }

    int i = 0;
    while (fread(&real[i++], sizeof(float), 1, fp_r)>0)
        ;
    
    i = 0;
    while (fread(&imag[i++], sizeof(float), 1, fp_i)>0)
        ;

    for (i=0; i!=600; ++i) {
        printf("no=%d,real=%f,imag=%f\n", i, real[i], imag[i]);
    }

    fclose(fp_r);
    fclose(fp_i);

    float sum_real[2] = {0.0f};
    float sum_imag[2] = {0.0f};

    float avg_real[2] = {0.0f};
    float avg_imag[2] = {0.0f};
    
    for (int i=0; i!=2; ++i) {
        for (int j=0; j!=d; ++j) {
            sum_real[i] += DMRSSeq[i][j].m_real - real[i*300+j];
            sum_imag[i] += DMRSSeq[i][j].m_imag - imag[i*300+j];
            //printf("no %d, the value of seq: %f, %f\n", j, d[i][j].m_real, d[i][j].m_imag);
        }
        avg_real[i] = sum_real[i] / 300.0;
        avg_imag[i] = sum_imag[i] / 300.0;
        printf("slot:%d, sum_real[%d]=%f, avg_real[%d]=%f\n", i+1, i, sum_real[i], i, avg_real[i]);
        printf("slot:%d, sum_imag[%d]=%f, avg_imag[%d]=%f\n", i+1, i, sum_imag[i], i, avg_imag[i]);
    }


#endif
    return 0;
}

