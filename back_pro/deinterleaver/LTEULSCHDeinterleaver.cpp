#include "LTEULSCHDeinterleaver.h"

#include <math.h>

int LTEULSCHDeinterleaver::Deinterleaver(float *quantizedDemodulationLLRsData)
{
    int retDataLen;
    double tableBetaACK[16] = {2.000, 2.500, 3.125, 4.000, 5.000, 6.250, 8.000, 10.000, 12.625, 15.875, 20.000, 31.000, 50.000, 80.000, 126.000, -1}; 
	double tableBetaRI[16] = {1.250, 1.625, 2.000, 2.500, 3.125, 4.000, 5.000, 6.250, 8.000, 10.000, 12.625, 15.875, 20.000, -1, -1, -1};
	double tableBetaCQI[16] = {-1, -1, 1.125, 1.250, 1.375, 1.625, 1.750, 2.000, 2.250, 2.500, 2.875, 3.125, 3.500, 4.000, 5.000, 6.250};
    double betaACK = tableBetaACK[m_BetaIndex.m_ACKOffset];
    double betaRI = tableBetaRI[m_BetaIndex.m_RIOffset];
    double betaCQI = tableBetaCQI[m_BetaIndex.m_CQIOffset];

    unsigned char modulationLevel;
    if (LTEQPSK == m_ModulationLevel)
        modulationLevel = 2;
    else if (LTE16QAM == m_ModulationLevel)
        modulationLevel = 4;
    else if (LTE64QAM == m_ModulationLevel)
        modulationLevel = 6;
    
    unsigned short mPUSCH = m_AssignedRBs * 12;

    unsigned char nPUSCH;
    if (!m_SRSFlag)
        nPUSCH = 12;
    else
        nPUSCH = 11;

   // int sumKr = m_SumKr;
   double qTmp;
   int qPrime, qACK, qRI, qCQI;

   //get qACK
   qTmp = static_cast<double>(m_CtrlInfoBits.m_ACKBits) * static_cast<double>(mPUSCH) * 
       static_cast<double>(nPUSCH) * betaACK /  static_cast<double>(m_SumKr);
   qPrime = ceil(qTmp);
   if (qPrime > mPUSCH*4)
       qPrime = mPUSCH * 4;
   qACK = qPrime * modulationLevel;
   //get qRI
   qTmp = static_cast<double>(m_CtrlInfoBits.m_RIBits) * static_cast<double>(mPUSCH) * 
       static_cast<double>(nPUSCH) * betaRI /  static_cast<double>(m_SumKr);
   qPrime = ceil(qTmp);
   if (qPrime > mPUSCH*4)
       qPrime = mPUSCH * 4;
   qRI = qPrime * modulationLevel;
   //get qCQI
   int lCRCBits;
   if (m_CtrlInfoBits.m_CQIBits > 11)
       lCRCBits = 8;
   else
       lCRCBits = 0;
   qTmp = static_cast<double>(m_CtrlInfoBits.m_CQIBits+lCRCBits) * static_cast<double>(mPUSCH) *
       static_cast<double>(nPUSCH) * betaCQI / static_cast<double>(m_SumKr);
   qPrime = ceil(qTmp);
   if (qPrime > (mPUSCH*nPUSCH - qRI/modulationLevel))
       qPrime = mPUSCH*nPUSCH - qRI/modulationLevel;
   qCQI = qPrime * modulationLevel;

   unsigned char tableTypeAllRE[1200][12] = {0x00}; //0:data,1:CQI,2:RI,3:ACK,4:CQI+ACK
   int rTmp, iTmp, jTmp, cTmp, symbolIndex;

   //find RI location
   int lengthRISymbols = qRI / modulationLevel;
   int recordRILocationIndex = 0;
   int recordRILocation[1000];
   unsigned char tableRIColumn[4] = {0x01, 0x04, 0x07, 0x0a};
   float dataRILLR[4800] = {0.0f};
   if (qRI > 0) {
       rTmp = mPUSCH - 1;
       iTmp = 0;
       jTmp = 0;
       while (iTmp < (qRI/modulationLevel)) {
           cTmp = tableRIColumn[jTmp];
           tableTypeAllRE[rTmp][cTmp] = 2;
           symbolIndex = cTmp * mPUSCH + rTmp;  //
            for (int mm=0; mm<modulationLevel; ++mm) {
                dataRILLR[iTmp*modulationLevel+mm] 
                    = m_QuantizedDemodulationLLRs[symbolIndex*modulationLevel+mm];
                recordRILocation[recordRILocationIndex++]
                    = symbolIndex * modulationLevel + mm;
            }
            iTmp++;
            rTmp = mPUSCH - 1 - (iTmp/4);
            jTmp = (jTmp + 3) % 4;
       }
   }

   //find ACK location
   int lengthACKSymbols = qACK / modulationLevel;
   int recordACKLocationIndex = 0;
   int recordACKLocation[1000];
   unsigned char tableACKColumn[4] = {0x02, 0x03, 0x08, 0x09};
   float dataACKLLR[4800] = {0.0f};
   if (qACK > 0) {
       rTmp = mPUSCH - 1;
       iTmp = 0;
       jTmp = 0;
       while (iTmp < (qACK/modulationLevel)) {
           cTmp = tableACKColumn[jTmp];
           tableTypeAllRE[rTmp][cTmp] = 3;
           symbolIndex = cTmp * mPUSCH + rTmp;
           for (int mm=0; mm<modulationLevel; ++mm) {
               dataACKLLR[iTmp*modulationLevel+mm]
                   = m_QuantizedDemodulationLLRs[symbolIndex*modulationLevel+mm];
               recordACKLocation[recordACKLocationIndex++]
                   = symbolIndex * modulationLevel + mm;
           }
           iTmp++;
           rTmp = mPUSCH - 1 - (iTmp/4);
           jTmp = (jTmp + 3) % 4;
       }
   }

   //find CQI location
   if (qCQI > 0) {
       iTmp = 0;
       rTmp = 0;
       cTmp = 0;
       while (iTmp < (qCQI/modulationLevel)) {
           if (2 != tableTypeAllRE[rTmp][cTmp]) {   //avoid RI
               if (3 == tableTypeAllRE[rTmp][cTmp]) {   //ACK
                   tableTypeAllRE[rTmp][cTmp] = 4;
               } else {
                   tableTypeAllRE[rTmp][cTmp] = 1;
               }
           }
           cTmp++;
           if (cTmp == nPUSCH) {
               cTmp = 0;
               rTmp++;
           }
       }
   }

   //extract data, CQI
   int indexCQI = 0, indexData = 0;
   for (int rowIndex=0; rowIndex<mPUSCH; ++rowIndex) {
       for (int colIndex=0; colIndex<nPUSCH; ++colIndex) {
           symbolIndex = colIndex * mPUSCH + rowIndex;
           if (0 == tableTypeAllRE[rowIndex][colIndex]) {
               for (int mm=0; mm<modulationLevel; ++mm) {
                   quantizedDemodulationLLRsData[indexData*modulationLevel+mm]
                       = m_QuantizedDemodulationLLRs[symbolIndex*modulationLevel+mm];
               }
               indexData++;
           } else if (3 == tableTypeAllRE[rowIndex][colIndex]) {
               for (int mm=0; mm<modulationLevel; ++mm) {
                   quantizedDemodulationLLRsData[indexData*modulationLevel+mm] = 0;
               }
               indexData++;
           } else if (1 == tableTypeAllRE[rowIndex][colIndex]) {
               for (int mm=0; mm<modulationLevel; ++mm) {
                   //dataCQI
               }
               indexCQI++;
           } else if (4 == tableTypeAllRE[rowIndex][colIndex]) {
               for (int mm=0; mm<modulationLevel; ++mm)
                   ;    //dataCQI
               indexCQI++;
           }
       }
   }

   return retDataLen;
}

