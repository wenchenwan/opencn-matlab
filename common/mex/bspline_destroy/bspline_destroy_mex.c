#include "c_spline.h"
#include <mex.h>
#include <string.h>

// c_bspline_destroy_wrapper(Bl)

static void usage() { mexErrMsgTxt("Usage: c_bspline_destroy_wrapper(Bl)\n"); }

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 1) {
        usage();
    }

    if (nlhs != 0) {
        usage();
    }

    if (!mxIsStruct(prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgTxt("c_bspline_destroy_wrapper: Bl must be a single struct\n");
    }

    mxArray *handle_in = mxGetFieldByNumber(prhs[0], 0, 0);
    if (!mxIsClass(handle_in, "uint64")) {
        mexErrMsgTxt("c_bspline_destroy_wrapper: Bl.handle must be an uint64\n");
    }
    uint64_t handle = ((uint64_t *)mxGetPr(handle_in))[0];
    c_bspline_destroy(&handle);
}
