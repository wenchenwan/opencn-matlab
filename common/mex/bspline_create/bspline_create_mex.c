#include "c_spline.h"
#include <mex.h>
#include <string.h>

// Bl = c_bspline_create_wrapper(x0, x1, deg, nbreak)

static void usage() { mexErrMsgTxt("Usage: Bl = c_bspline_create_wrapper(x0, x1, deg, nbreak)\n"); }

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 4) {
        usage();
    }

    if (nlhs != 1) {
        usage();
    }

    if (!mxIsDouble(prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgTxt("c_bspline_create_wrapper: x0 must be a double scalar\n");
    }

    if (!mxIsDouble(prhs[1]) || mxGetNumberOfElements(prhs[1]) != 1) {
        mexErrMsgTxt("c_bspline_create_wrapper: x1 must be a double scalar\n");
    }
    
    if (!mxIsDouble(prhs[2])|| mxGetNumberOfElements(prhs[2]) != 1) {
        mexErrMsgTxt("c_bspline_create_wrapper: deg must be a double scalar\n");
    }

    if (!mxIsDouble(prhs[3])|| mxGetNumberOfElements(prhs[3]) != 1) {
        mexErrMsgTxt("c_bspline_create_wrapper: nbreak must be a double scalar\n");
    }

    // @TODO Check x1 > x0, nbreak > 0, deg > 0
    uint64_t handle;
    double x0 = mxGetPr(prhs[0])[0];
    double x1 = mxGetPr(prhs[1])[0];
    size_t deg = (size_t)mxGetPr(prhs[2])[0];
    size_t nbreak = (size_t)mxGetPr(prhs[3])[0];
    c_bspline_create(&handle, x0, x1, deg, nbreak);

    mxArray *spline_n = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
    ((uint64_t *)mxGetPr(spline_n))[0] = nbreak + deg - 2;

    mxArray *handle_out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    ((uint64_t *)mxGetPr(handle_out))[0] = handle;

    char *fieldnames[2];
    fieldnames[0] = (char *)mxMalloc(20);
    fieldnames[1] = (char *)mxMalloc(20);

    strcpy(fieldnames[0], "handle");
    strcpy(fieldnames[1], "n");

    plhs[0] = mxCreateStructMatrix(1, 1, 2, (const char **)fieldnames);
    mxSetFieldByNumber(plhs[0], 0, 0, handle_out);
    mxSetFieldByNumber(plhs[0], 0, 1, spline_n);
}
