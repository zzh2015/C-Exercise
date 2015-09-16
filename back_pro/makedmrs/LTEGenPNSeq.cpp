#include "LTEGenPNSeq.h"

LTEGenPNSeq::LTEGenPNSeq()
{
}

LTEGenPNSeq::~LTEGenPNSeq()
{
}
/** generate Gold sequence
 * @param [in] num_points sequence length
 * @param [in] c_init seed
 * @param [out] PN_bits_ptr output pointer
 */
void LTEGenPNSeq::MakeSequence(int num_points, int c_init, char* PN_bits_ptr)
{
    int x1, x2, new_bit;
    // initialize x1 and x2
    x1 = 0x01;
    x2 = c_init;
    // fill the x1 and x2 sequences up to 1600
    for(int loop = 1; loop < 1600; ++loop)
    {
        new_bit = ((x1 & 0x08) >> 3) ^ (x1 & 0x01);
        new_bit <<= 30;
        x1 = (x1 >> 1) | new_bit;

        new_bit = ((x2 & 0x08) >> 3) ^ ((x2 & 0x04) >> 2) ^ ((x2 & 0x02) >> 1) ^ (x2 & 0x01);
        new_bit <<= 30;
        x2 = (x2 >> 1) | new_bit;
    }
    // continue filling the x1 and x2 sequences and fill the output
    for(int loop = 0; loop < num_points; ++loop)
    {
        new_bit = ((x1 & 0x08) >> 3) ^ (x1 & 0x01);
        new_bit <<= 30;
        x1 = (x1 >> 1) | new_bit;

        new_bit = ((x2 & 0x08) >> 3) ^ ((x2 & 0x04) >> 2) ^ ((x2 & 0x02) >> 1) ^ (x2 & 0x01);
        new_bit <<= 30;
        x2 = (x2 >> 1) | new_bit;

        PN_bits_ptr[loop] = (x1 & 0x01) ^ (x2 & 0x01);
    }
}
