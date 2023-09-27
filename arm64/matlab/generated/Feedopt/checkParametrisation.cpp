//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkParametrisation.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:27:31
//

// Include Files
#include "checkParametrisation.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include <cmath>

// Function Definitions
//
// function [ valid ] = checkParametrisation( queue )
//
// checkParametrisation : Check if the parametrisation of the curve is
//  valide
//
// Arguments    : const queue_coder *queue
// Return Type  : bool
//
namespace ocn {
bool checkParametrisation(const queue_coder *queue)
{
    CurvStruct expl_temp;
    unsigned int N;
    bool valid;
    // 'checkParametrisation:5' valid = false;
    valid = false;
    // 'checkParametrisation:7' N = queue.size;
    N = queue->size();
    // 'checkParametrisation:9' if( N == 0 )
    if (N == 0U) {
        // 'checkParametrisation:10' valid = true;
        valid = true;
    } else {
        double curv_a_param;
        double curv_b_param;
        bool valide;
        CurveType curv_Info_Type;
        // 'checkParametrisation:14' curv = queue.get( 1 );
        queue->get(static_cast<double>(1.0), &expl_temp);
        curv_Info_Type = expl_temp.Info.Type;
        curv_a_param = expl_temp.a_param;
        curv_b_param = expl_temp.b_param;
        // 'checkParametrisation:16' if( ~valid_curv_param( curv ) )
        // 'checkParametrisation:43' valide = false;
        valide = false;
        // 'checkParametrisation:44' if( curv.a_param <= 0 )
        if ((expl_temp.a_param > 0.0) && (expl_temp.b_param >= 0.0) &&
            ((expl_temp.a_param + expl_temp.b_param) - 1.0 <= 2.2204460492503131E-16)) {
            // 'checkParametrisation:45' if( curv.b_param < 0 )
            // 'checkParametrisation:46' if( curv.a_param + curv.b_param -1 > eps )
            // 'checkParametrisation:47' valide = true;
            valide = true;
        }
        if (valide) {
            unsigned int k;
            // 'checkParametrisation:18' for k = 2 : N
            k = 2U;
            int exitg1;
            do {
                exitg1 = 0;
                if (k <= N) {
                    bool b_valide;
                    // 'checkParametrisation:19' curvNext = queue.get( k );
                    queue->get(k, &expl_temp);
                    // 'checkParametrisation:21' if( ~valid_curv_param( curvNext ) )
                    // 'checkParametrisation:43' valide = false;
                    b_valide = false;
                    // 'checkParametrisation:44' if( curv.a_param <= 0 )
                    if ((expl_temp.a_param > 0.0) && (expl_temp.b_param >= 0.0) &&
                        ((expl_temp.a_param + expl_temp.b_param) - 1.0 <= 2.2204460492503131E-16)) {
                        // 'checkParametrisation:45' if( curv.b_param < 0 )
                        // 'checkParametrisation:46' if( curv.a_param + curv.b_param -1 > eps )
                        // 'checkParametrisation:47' valide = true;
                        b_valide = true;
                    }
                    if (!b_valide) {
                        exitg1 = 1;
                    } else {
                        bool guard1;
                        // 'checkParametrisation:23' if( curvNext.Info.Type == CurveType.TransP5 )
                        // || ... 'checkParametrisation:24'       ( curv.Info.Type ==
                        // CurveType.TransP5 )
                        guard1 = false;
                        if ((expl_temp.Info.Type == CurveType_TransP5) ||
                            (curv_Info_Type == CurveType_TransP5)) {
                            guard1 = true;
                        } else {
                            double d;
                            // 'checkParametrisation:25' else
                            // 'checkParametrisation:26' if( abs( ( curv.b_param + curv.a_param ) -
                            // 1 ) > eps )
                            d = curv_b_param + curv_a_param;
                            if ((std::abs(d - 1.0) > 2.2204460492503131E-16) &&
                                (std::abs(expl_temp.b_param - d) > 2.2204460492503131E-16)) {
                                // 'checkParametrisation:27' if( abs( curvNext.b_param - (
                                // curv.b_param + curv.a_param ) ) > eps )
                                exitg1 = 1;
                            } else {
                                guard1 = true;
                            }
                        }
                        if (guard1) {
                            // 'checkParametrisation:33' curv = curvNext;
                            curv_Info_Type = expl_temp.Info.Type;
                            curv_a_param = expl_temp.a_param;
                            curv_b_param = expl_temp.b_param;
                            k++;
                        }
                    }
                } else {
                    // 'checkParametrisation:36' if( curv.b_param + curv.a_param < 1 )
                    if (curv_b_param + curv_a_param >= 1.0) {
                        // 'checkParametrisation:38' valid = true;
                        valid = true;
                    }
                    exitg1 = 1;
                }
            } while (exitg1 == 0);
        }
    }
    return valid;
}

} // namespace ocn

//
// File trailer for checkParametrisation.cpp
//
// [EOF]
//
