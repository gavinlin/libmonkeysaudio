#pragma once

namespace APE
{

#include "RollBuffer.h"
#define NN_WINDOW_ELEMENTS    512

class CNNFilter
{
public:
    CNNFilter(int nOrder, int nShift, int nVersion);
    ~CNNFilter();

    int Compress(int nInput);
    int Decompress(int nInput);
    void Flush();

private:
    int m_nOrder;
    int m_nShift;
    int m_nVersion;
    int m_nRunningAverage;
    APE::CRollBuffer<short> m_rbInput;
    APE::CRollBuffer<short> m_rbDeltaM;
    short * m_paryM;
	#ifdef ENABLE_SSE_ASSEMBLY
		BOOL m_bSSEAvailable;
	#endif

    __forceinline short GetSaturatedShortFromInt(int nValue) const
    {
        return short((nValue == short(nValue)) ? nValue : (nValue >> 31) ^ 0x7FFF);
    }

    __forceinline void Adapt(short * pM, short * pAdapt, int nDirection, int nOrder);
    __forceinline int CalculateDotProduct(short * pA, short * pB, int nOrder);
    
	#ifdef ENABLE_SSE_ASSEMBLY
		__forceinline void AdaptSSE(short * pM, short * pAdapt, int nDirection, int nOrder);
		__forceinline int CalculateDotProductSSE(short * pA, short * pB, int nOrder);
	#endif
};

}
