/***********************************************************************
> Copyright: 2015, Innovem Tech. Co., Ltd.
> FileName:  LTEULSCHDeinterleaver.h
***********************************************************************/
#ifndef _LTEULSCHDEINTERLEAVER_H_
#define _LTEULSCHDEINTERLEAVER_H_
typedef enum {
    LTEBPSK,
    LTEQPSK,
    LTE16QAM,
    LTE64QAM
}LTEModulationType;

typedef struct PUSCHBetaIndex {
    unsigned char m_ACKOffset;  // 3 index
    unsigned char m_RIOffset;
    unsigned char m_CQIOffset;
}PUSCHBetaIndex;

typedef struct ControlInfoBits {
    int m_ACKBits;  //3 bits
    int m_RIBits;
    int m_CQIBits;
}ControlInfoBits;

class LTEULSCHDeinterleaver {
    public:
        LTEULSCHDeinterleaver() {}
        LTEULSCHDeinterleaver(PUSCHBetaIndex index, ControlInfoBits bits, unsigned short assignedRbs, 
                bool flag, unsigned char level, int kr, float *qd) :
            m_BetaIndex(index), m_CtrlInfoBits(bits), m_AssignedRBs(assignedRbs),
            m_ModulationLevel(flag), m_SumKr(kr), m_QuantizedDemodulationLLRs(qd) {}
        ~LTEULSCHDeinterleaver() = default;
        LTEULSCHDeinterleaver(const LTEULSCHDeinterleaver&) = delete;
        LTEULSCHDeinterleaver &operator=(const LTEULSCHDeinterleaver&) = delete;
        
        int Deinterleaver(float*);
    protected:

    private:
        PUSCHBetaIndex m_BetaIndex;
        ControlInfoBits m_CtrlInfoBits;
        unsigned short m_AssignedRBs;
        bool m_SRSFlag; //srs flag,set value 11 or 12
        unsigned char m_ModulationLevel;    //Qm 2,4,6
        int m_SumKr;
        float *m_QuantizedDemodulationLLRs;
};

#endif  //_LTEULSCHDEINTERLEAVER_H_

