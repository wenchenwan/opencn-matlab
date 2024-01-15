
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkZSpdmode.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "checkZSpdmode.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"

// Function Definitions
//
// function [ valid, ctx ] = checkZSpdmode( ctx, queue )
//
// checkZSpdmode : Check if the curve has valid zero speed mode.
//
//  Inputs :
//    ctx     : The context of the computational chain
//    queue   : The queue of curvs
//
//  Outputs :
//    valid   : Is a valid Zero Speed Mode
//    ctx     : The context of the computatinal chain
//
//
// Arguments    : b_FeedoptContext *ctx
//                const queue_coder *queue
// Return Type  : bool
//
namespace ocn {
bool checkZSpdmode(b_FeedoptContext *ctx, const queue_coder *queue)
{
    CurvStruct expl_temp;
    unsigned int N;
    bool valid;
    // 'checkZSpdmode:12' valid = false;
    valid = false;
    // 'checkZSpdmode:14' N = queue.size;
    N = queue->size();
    // 'checkZSpdmode:16' if( N == 0 )
    if (N == 0U) {
        // 'checkZSpdmode:17' valid = true;
        valid = true;
    } else {
        unsigned int k;
        ZSpdMode curv_Info_zspdmode;
        // 'checkZSpdmode:21' ctx.programmed_stop = int32( 0 );
        ctx->programmed_stop = 0;
        // 'checkZSpdmode:23' curv = queue.get( 1 );
        queue->get(&expl_temp);
        curv_Info_zspdmode = expl_temp.Info.zspdmode;
        // 'checkZSpdmode:25' for k = 2 : N
        k = 2U;
        int exitg1;
        do {
            exitg1 = 0;
            if (k <= N) {
                bool guard1;
                bool guard2;
                bool zeroFlag;
                // 'checkZSpdmode:26' curvNext = queue.get( k );
                queue->get(k, &expl_temp);
                // 'checkZSpdmode:28' if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
                // 'checkZSpdmode:29'        ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
                //  isAZeroEnd : Return true if the curv ends with zero speed
                //
                //  Inputs :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                //
                //  Outputs :
                //  zeroFlag : Boolean value. TRUE mean zero flag
                // 'isAZeroEnd:10' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroEnd:12' [zspdmode, error] = getZspdmode( speed );
                //  getZspdmode: Get the current zero speed mode
                //
                //  Inputs :
                //    speed    : structure with zspdmode for the speed
                //
                //  Outputs :
                //    zspdmode : Zero speed mode
                //    error    : Error bolean value. TRUE if no zspdmode has been found.
                //
                // 'getZspdmode:13' error = false;
                // 'getZspdmode:15' if( isenum( speed ) )
                // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                // 'isAZeroEnd:14' if( error )
                // 'isAZeroEnd:16' if( zspdmode == ZSpdMode.NZ || ...
                // 'isAZeroEnd:17'     zspdmode == ZSpdMode.ZZ )
                if ((curv_Info_zspdmode == ZSpdMode_NZ) || (curv_Info_zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroEnd:18' zeroFlag = true;
                    zeroFlag = true;
                }
                guard1 = false;
                guard2 = false;
                if (zeroFlag) {
                    bool b_zeroFlag;
                    //  isAZeroStart : Return true if the curv starts with zero speed
                    //
                    //  Inputs :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    //
                    //  Outputs :
                    //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
                    //
                    // 'isAZeroStart:11' zeroFlag = false;
                    b_zeroFlag = false;
                    // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
                    //  getZspdmode: Get the current zero speed mode
                    //
                    //  Inputs :
                    //    speed    : structure with zspdmode for the speed
                    //
                    //  Outputs :
                    //    zspdmode : Zero speed mode
                    //    error    : Error bolean value. TRUE if no zspdmode has been found.
                    //
                    // 'getZspdmode:13' error = false;
                    // 'getZspdmode:15' if( isenum( speed ) )
                    // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroStart:15' if( error )
                    // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
                    // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
                    if ((expl_temp.Info.zspdmode == ZSpdMode_ZN) ||
                        (expl_temp.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroStart:19' zeroFlag = true;
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
                    //
                    //  Inputs :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    //
                    //  Outputs :
                    //  zeroFlag : Boolean value. TRUE mean zero flag
                    // 'isAZeroEnd:10' zeroFlag = false;
                    c_zeroFlag = false;
                    // 'isAZeroEnd:12' [zspdmode, error] = getZspdmode( speed );
                    //  getZspdmode: Get the current zero speed mode
                    //
                    //  Inputs :
                    //    speed    : structure with zspdmode for the speed
                    //
                    //  Outputs :
                    //    zspdmode : Zero speed mode
                    //    error    : Error bolean value. TRUE if no zspdmode has been found.
                    //
                    // 'getZspdmode:13' error = false;
                    // 'getZspdmode:15' if( isenum( speed ) )
                    // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:14' if( error )
                    // 'isAZeroEnd:16' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:17'     zspdmode == ZSpdMode.ZZ )
                    if ((curv_Info_zspdmode == ZSpdMode_NZ) ||
                        (curv_Info_zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:18' zeroFlag = true;
                        c_zeroFlag = true;
                    }
                    if (!c_zeroFlag) {
                        bool d_zeroFlag;
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //
                        //  Inputs :
                        //  curv / Info / ZSpdMode : A structure containning the information of the
                        //  curv zero speed.
                        //
                        //  Outputs :
                        //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
                        //
                        // 'isAZeroStart:11' zeroFlag = false;
                        d_zeroFlag = false;
                        // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
                        //  getZspdmode: Get the current zero speed mode
                        //
                        //  Inputs :
                        //    speed    : structure with zspdmode for the speed
                        //
                        //  Outputs :
                        //    zspdmode : Zero speed mode
                        //    error    : Error bolean value. TRUE if no zspdmode has been found.
                        //
                        // 'getZspdmode:13' error = false;
                        // 'getZspdmode:15' if( isenum( speed ) )
                        // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                        // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                        // 'isAZeroStart:15' if( error )
                        // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
                        if ((expl_temp.Info.zspdmode == ZSpdMode_ZN) ||
                            (expl_temp.Info.zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroStart:19' zeroFlag = true;
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
                    // 'checkZSpdmode:33' if( isAZeroSpeed( curv ) )
                    //  isAZeroSpeed : Return true if the curv is has a zero speed
                    //
                    //  Inputs :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero
                    //
                    //  Outputs :
                    //  zeroFlag : Boolean value. TRUE means zero speed structure.
                    //
                    // 'isAZeroSpeed:12' zeroFlag = false;
                    // 'isAZeroSpeed:14' [zspdmode, error] = getZspdmode( speed );
                    //  getZspdmode: Get the current zero speed mode
                    //
                    //  Inputs :
                    //    speed    : structure with zspdmode for the speed
                    //
                    //  Outputs :
                    //    zspdmode : Zero speed mode
                    //    error    : Error bolean value. TRUE if no zspdmode has been found.
                    //
                    // 'getZspdmode:13' error = false;
                    // 'getZspdmode:15' if( isenum( speed ) )
                    // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroSpeed:16' if( error )
                    // 'isAZeroSpeed:18' zeroFlag = ( zspdmode ~= ZSpdMode.NN );
                    if (curv_Info_zspdmode != ZSpdMode_NN) {
                        // 'checkZSpdmode:34' ctx.programmed_stop = ctx.programmed_stop + 1;
                        ctx->programmed_stop++;
                    }
                    // 'checkZSpdmode:37' curv = curvNext;
                    curv_Info_zspdmode = expl_temp.Info.zspdmode;
                    k++;
                }
            } else {
                // 'checkZSpdmode:40' valid = true;
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
