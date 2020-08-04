#include "c_spline.h"
#include <mex.h>
#include <string.h>

// [BasisVal, BasisValD, BasisValDD, BasisIntegr] = c_bspline_base_eval_wrapper(Bl, xvec)

static void usage() {
    mexErrMsgTxt("Usage: [BasisVal, BasisValD, BasisValDD, BasisIntegr] = c_bspline_base_eval_wrapper(Bl, xvec)\n");
}

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 2) {
        usage();
    }

    if (nlhs != 4) {
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

    size_t N = mxGetNumberOfElements(prhs[1]);

    plhs[0] = mxCreateDoubleMatrix(N, n, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(N, n, mxREAL);
    plhs[2] = mxCreateDoubleMatrix(N, n, mxREAL);
    plhs[3] = mxCreateDoubleMatrix(n, 1, mxREAL);

    c_bspline_base_eval(&handle, N, mxGetPr(prhs[1]), mxGetPr(plhs[0]), mxGetPr(plhs[1]), mxGetPr(plhs[2]),
                        mxGetPr(plhs[3]));
}
