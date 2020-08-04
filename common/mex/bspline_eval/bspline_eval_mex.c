#include "c_spline.h"
#include <mex.h>
#include <string.h>

// [x, xd, xdd] = c_bspline_eval_wrapper(Bl, coeffs, x)

static void usage() { mexErrMsgTxt("Usage: [x, xd, xdd] = c_bspline_eval_wrapper(Bl, coeffs, x) \n"); }

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 3) {
        usage();
    }

    if (nlhs != 3) {
        usage();
    }

    if (!mxIsStruct(prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgTxt("c_bspline_eval_wrapper: Bl must be a single struct\n");
    }

    mxArray *handle_in = mxGetFieldByNumber(prhs[0], 0, 0);
    if (!mxIsClass(handle_in, "uint64")) {
        mexErrMsgTxt("c_bspline_eval_wrapper: Bl.handle must be an uint64\n");
    }
    uint64_t handle = ((uint64_t *)mxGetPr(handle_in))[0];

    mxArray *n_in = mxGetFieldByNumber(prhs[0], 0, 1);
    if (!mxIsClass(n_in, "uint32")) {
        mexErrMsgTxt("c_bspline_eval_wrapper: Bl.n must be an uint32\n");
    }
    uint64_t n = ((uint32_t *)mxGetPr(n_in))[0];

    if (mxGetNumberOfElements(prhs[1]) != n) {
        mexErrMsgIdAndTxt("MATLAB:c_bspline_eval_wrapper:coeffs",
                          " coeffs has a wrong number of elements: got %d, expected %d\n",
                          mxGetNumberOfElements(prhs[1]), n);
    }

    if (mxGetNumberOfElements(prhs[2]) != 1) {
        mexErrMsgTxt("c_bspline_eval_wrapper: x must be an scalar\n");
    }

    double X[3];
    c_bspline_eval(&handle, mxGetPr(prhs[1]), mxGetPr(prhs[2])[0], X);

    plhs[0] = mxCreateDoubleScalar(X[0]);
    plhs[1] = mxCreateDoubleScalar(X[1]);
    plhs[2] = mxCreateDoubleScalar(X[2]);
}
