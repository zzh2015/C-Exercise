/***********************************************************************
> Copyright: 2015, Innovem Tech. Co., Ltd.
> FileName: LTEGenPUSCHDMRSSeq.h
***********************************************************************/

#ifndef LTEGENPUSCHDMRSSEQ_H
#define LTEGENPUSCHDMRSSEQ_H

//#include "Complex.h"
class Complex;

typedef struct DMRSSeqConfig {
    int m_CellID;
    int m_IndexCurrentSubframe;
    int m_LengthPRB;
    bool m_SeqHoppingEnabled;
    bool m_GroupHoppingEnabled;
    int m_GroupAssignmentPUSCH;
    int m_CyclicShiftHighLayer;
    int m_CyclicShiftHighLayerDCI0;
}DMRSSeqConfig;

class LTEGenPUSCHDMRSSeq
{
public:
    LTEGenPUSCHDMRSSeq();

    int GenetatePUSCHDMRSSeq(DMRSSeqConfig *dmrsSeqConfig, Complex dmrsSeq[][1200]);
#if 0
    LTEGenPUSCHDMRSSeq(const LTEGenPUSCHDMRSSeq&) = delete; //阻止拷贝
    LTEGenPUSCHDMRSSeq &operator=(const LTEGenPUSCHDMRSSeq&) = delete;
    ~LTEGenPUSCHDMRSSeq() = default;    //使用默认析够函数
    //Config data
    DMRSSeqConfig m_DMRSSeqConfig;
#endif
};

#endif // LTEGENPUSCHDMRSSEQ_H

