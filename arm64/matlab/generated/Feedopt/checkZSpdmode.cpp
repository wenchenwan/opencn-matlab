//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkZSpdmode.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:48:46
//

// Include Files
#include "checkZSpdmode.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"

// Function Definitions
//
// function [ valid ] = checkZSpdmode( queue )
//
// checkZSpdmode : Check if the curve has valid zero speed mode
//
// Arguments    : const queue_coder *queue
// Return Type  : bool
//
namespace ocn {
bool checkZSpdmode(const queue_coder *queue)
{
    CurvStruct expl_temp;
    unsigned int N;
    unsigned int k;
    bool valid;
    ZSpdMode curv_Info_zspdmode;
    // 'checkZSpdmode:4' valid = false;
    valid = false;
    // 'checkZSpdmode:6' N = queue.size;
    N = queue->size();
    // 'checkZSpdmode:8' curv = queue.get( 1 );
    queue->get(&expl_temp);
    curv_Info_zspdmode = expl_temp.Info.zspdmode;
    // 'checkZSpdmode:10' for k = 2 : N
    k = 2U;
    int exitg1;
    do {
        exitg1 = 0;
        if (k <= N) {
            // 'checkZSpdmode:11' curvNext = queue.get( k );
            queue->get(k, &expl_temp);
            // 'checkZSpdmode:13' if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
            // 'checkZSpdmode:14'        ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
            //  isAZeroEnd : Return true if the curv ends with zero speed
            //  Input :
            //  curv  : The curve struct
            // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
            // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
            if ((((curv_Info_zspdmode == ZSpdMode_NZ) || (curv_Info_zspdmode == ZSpdMode_ZZ)) &&
                 ((expl_temp.Info.zspdmode != ZSpdMode_ZN) &&
                  (expl_temp.Info.zspdmode != ZSpdMode_ZZ))) ||
                ((curv_Info_zspdmode != ZSpdMode_NZ) && (curv_Info_zspdmode != ZSpdMode_ZZ) &&
                 ((expl_temp.Info.zspdmode == ZSpdMode_ZN) ||
                  (expl_temp.Info.zspdmode == ZSpdMode_ZZ)))) {
                // 'isAZeroEnd:7' zeroFlag = true;
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  curv  : The curve struct
                // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                // 'isAZeroStart:8' zeroFlag = false;
                // 'isAZeroEnd:9' zeroFlag = false;
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  curv  : The curve struct
                // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
                // 'isAZeroStart:6' zeroFlag = true;
                exitg1 = 1;
            } else {
                // 'isAZeroEnd:9' zeroFlag = false;
                // 'isAZeroStart:6' zeroFlag = true;
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv  : The curve struct
                // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
                // 'isAZeroEnd:7' zeroFlag = true;
                // 'isAZeroStart:8' zeroFlag = false;
                // 'checkZSpdmode:18' curv = curvNext;
                curv_Info_zspdmode = expl_temp.Info.zspdmode;
                k++;
            }
        } else {
            // 'checkZSpdmode:21' valid = true;
            valid = true;
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    return valid;
}

} // namespace ocn

//
// File trailer for checkZSpdmode.cpp
//
// [EOF]
//
