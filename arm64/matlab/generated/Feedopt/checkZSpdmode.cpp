//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkZSpdmode.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
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
    bool valid;
    // 'checkZSpdmode:4' valid = false;
    valid = false;
    // 'checkZSpdmode:6' N = queue.size;
    N = queue->size();
    // 'checkZSpdmode:8' if( N == 0 )
    if (N == 0U) {
        // 'checkZSpdmode:9' valid = true;
        valid = true;
    } else {
        unsigned int k;
        ZSpdMode curv_Info_zspdmode;
        // 'checkZSpdmode:13' curv = queue.get( 1 );
        queue->get(static_cast<double>(1.0), &expl_temp);
        curv_Info_zspdmode = expl_temp.Info.zspdmode;
        // 'checkZSpdmode:15' for k = 2 : N
        k = 2U;
        int exitg1;
        do {
            exitg1 = 0;
            if (k <= N) {
                bool guard1;
                bool guard2;
                bool zeroFlag;
                // 'checkZSpdmode:16' curvNext = queue.get( k );
                queue->get(k, &expl_temp);
                // 'checkZSpdmode:18' if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
                // 'checkZSpdmode:19'        ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //  Input :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                // 'isAZeroEnd:6' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                // 'getZspdmode:3' error = false;
                // 'getZspdmode:5' if( isenum( speed ) )
                // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                // 'isAZeroEnd:10' if( error )
                // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                if ((curv_Info_zspdmode == ZSpdMode_NZ) || (curv_Info_zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroEnd:14' zeroFlag = true;
                    zeroFlag = true;
                }
                guard1 = false;
                guard2 = false;
                if (zeroFlag) {
                    bool b_zeroFlag;
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroStart:6' zeroFlag = false;
                    b_zeroFlag = false;
                    // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroStart:10' if( error )
                    // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                    if ((expl_temp.Info.zspdmode == ZSpdMode_ZN) ||
                        (expl_temp.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:14' zeroFlag = true;
                        b_zeroFlag = true;
                    }
                    if (!b_zeroFlag) {
                        exitg1 = 1;
                    } else {
                        guard2 = true;
                    }
                } else {
                    guard2 = true;
                }
                if (guard2) {
                    bool c_zeroFlag;
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroEnd:6' zeroFlag = false;
                    c_zeroFlag = false;
                    // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:10' if( error )
                    // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                    if ((curv_Info_zspdmode == ZSpdMode_NZ) ||
                        (curv_Info_zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:14' zeroFlag = true;
                        c_zeroFlag = true;
                    }
                    if (!c_zeroFlag) {
                        bool d_zeroFlag;
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //  Input :
                        //  curv / Info / ZSpdMode : A structure containning the information of the
                        //  curv zero speed.
                        // 'isAZeroStart:6' zeroFlag = false;
                        d_zeroFlag = false;
                        // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                        //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                        // 'getZspdmode:3' error = false;
                        // 'getZspdmode:5' if( isenum( speed ) )
                        // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                        // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                        // 'isAZeroStart:10' if( error )
                        // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                        if ((expl_temp.Info.zspdmode == ZSpdMode_ZN) ||
                            (expl_temp.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroStart:14' zeroFlag = true;
                            d_zeroFlag = true;
                        }
                        if (d_zeroFlag) {
                            exitg1 = 1;
                        } else {
                            guard1 = true;
                        }
                    } else {
                        guard1 = true;
                    }
                }
                if (guard1) {
                    // 'checkZSpdmode:23' curv = curvNext;
                    curv_Info_zspdmode = expl_temp.Info.zspdmode;
                    k++;
                }
            } else {
                // 'checkZSpdmode:26' valid = true;
                valid = true;
                exitg1 = 1;
            }
        } while (exitg1 == 0);
    }
    return valid;
}

} // namespace ocn

//
// File trailer for checkZSpdmode.cpp
//
// [EOF]
//
