//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EnableDebugLog.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "EnableDebugLog.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_rtwutil.h"
#include "sinspace_types.h"
#include "sinspace_types11.h"

// Function Declarations
namespace ocn {
static void MultiWordIor(const unsigned int u1[], const unsigned int u2[], unsigned int y[]);

}

// Function Definitions
//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
namespace ocn {
static void MultiWordIor(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    for (int i{0}; i < 2; i++) {
        y[i] = u1[i] | u2[i];
    }
}

//
// Arguments    : DebugCfg cfg
// Return Type  : void
//
void EnableDebugLog(DebugCfg cfg)
{
    static const uint64m_T r1{
        {1U, 0U} // chunks
    };
    uint64m_T r;
    uint64m_T r2;
    uint64m_T r3;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    Double2MultiWord(DebugConfig, (unsigned int *)&r.chunks[0U]);
    uMultiWordShl((unsigned int *)&r1.chunks[0U],
                  static_cast<unsigned int>(static_cast<int>(cfg) - 1),
                  (unsigned int *)&r2.chunks[0U]);
    MultiWordIor((unsigned int *)&r.chunks[0U], (unsigned int *)&r2.chunks[0U],
                 (unsigned int *)&r3.chunks[0U]);
    DebugConfig = uMultiWord2Double((unsigned int *)&r3.chunks[0U]);
}

} // namespace ocn

//
// File trailer for EnableDebugLog.cpp
//
// [EOF]
//
