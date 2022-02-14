//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: IsEnabledDebugLog.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "IsEnabledDebugLog.h"
#include "sinspace_data.h"
#include "sinspace_rtwutil.h"
#include "sinspace_types11.h"

// Function Declarations
namespace ocn {
static bool uMultiWordNe(const unsigned int u1[], const unsigned int u2[]);

}

// Function Definitions
//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : bool
//
namespace ocn {
static bool uMultiWordNe(const unsigned int u1[], const unsigned int u2[])
{
    return uMultiWordCmp(u1, u2) != 0;
}

//
// Arguments    : void
// Return Type  : bool
//
bool IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {8U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

//
// Arguments    : void
// Return Type  : bool
//
bool b_IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {32U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

//
// Arguments    : void
// Return Type  : bool
//
bool c_IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {16U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

//
// Arguments    : void
// Return Type  : bool
//
bool d_IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {128U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

//
// Arguments    : void
// Return Type  : bool
//
bool e_IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {2U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

//
// Arguments    : void
// Return Type  : bool
//
bool f_IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {1U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

//
// Arguments    : void
// Return Type  : bool
//
bool g_IsEnabledDebugLog()
{
    static const uint64m_T r1{
        {4U, 0U} // chunks
    };
    static const uint64m_T r3{
        {0U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    MultiWordAnd((unsigned int *)&r.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    return uMultiWordNe((unsigned int *)&r2.chunks[0U], (unsigned int *)&r3.chunks[0U]);
}

} // namespace ocn

//
// File trailer for IsEnabledDebugLog.cpp
//
// [EOF]
//
