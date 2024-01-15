
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkParametrisationQueue.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "checkParametrisationQueue.h"
#include "opencn_matlab_types111.h"
#include "queue_coder.h"

// Function Definitions
//
// function [ valid ] = checkParametrisationQueue( queue )
//
// checkParametrisationQueue : Check whether the curv parametrisation is
//  correct or not.
//
//  Inputs :
//    queue       : A queue of curvStruct
//
//  Outputs :
//    valid       : Boolean value, TRUE means the parametrisation is sound
//  for all the curvs.
//
//
// Arguments    : const queue_coder *queue
// Return Type  : bool
//
namespace ocn {
bool checkParametrisationQueue(const queue_coder *queue)
{
    CurvStruct expl_temp;
    unsigned int N;
    bool valid;
    // 'checkParametrisationQueue:13' valid = false;
    valid = false;
    // 'checkParametrisationQueue:15' N = queue.size;
    N = queue->size();
    // 'checkParametrisationQueue:17' if( N == 0 )
    if (N == 0U) {
        // 'checkParametrisationQueue:18' valid = true;
        valid = true;
    } else {
        int k;
        // 'checkParametrisationQueue:22' for k = 1 : N
        k = 0;
        int exitg1;
        do {
            exitg1 = 0;
            if (k <= static_cast<int>(N) - 1) {
                bool b_valid;
                // 'checkParametrisationQueue:23' curv = queue.get( k );
                queue->get(k + 1U, &expl_temp);
                // 'checkParametrisationQueue:25' if( ~checkParametrisation( curv ) )
                //  checkParametrisation : Check whether the curv parametrisation is correct
                //  or not.
                //
                //  Inputs :
                //    curv        : A curvStruct
                //
                //  Outputs :
                //    valid       : Boolean value, TRUE means the parametrisation is sound.
                //
                // 'checkParametrisation:11' valid = false;
                b_valid = false;
                // 'checkParametrisation:12' if( ~(curv.a_param > 0 && curv.a_param <= 1) )
                if ((expl_temp.a_param > 0.0) && (expl_temp.a_param <= 1.0) &&
                    (expl_temp.b_param >= 0.0) && (expl_temp.b_param < 1.0) &&
                    ((expl_temp.a_param + expl_temp.b_param) - 1.0 <= 2.2204460492503131E-16)) {
                    // 'checkParametrisation:13' if( ~(curv.b_param >= 0 && curv.b_param < 1) )
                    // 'checkParametrisation:14' if( curv.a_param + curv.b_param -1 > eps )
                    // 'checkParametrisation:15' valid = true;
                    b_valid = true;
                }
                if (!b_valid) {
                    exitg1 = 1;
                } else {
                    k++;
                }
            } else {
                // 'checkParametrisationQueue:30' valid = true;
                valid = true;
                exitg1 = 1;
            }
        } while (exitg1 == 0);
    }
    return valid;
}

} // namespace ocn

//
// File trailer for checkParametrisationQueue.cpp
//
// [EOF]
//
