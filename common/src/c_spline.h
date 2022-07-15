#ifndef C_SPLINE_H
#define C_SPLINE_H

#include <stddef.h>
#ifndef __KERNEL__
#include <gsl/gsl_bspline.h>
#include <stdint.h>
#else
#include <linux/types.h>
#include <opencn/gsl/gsl_bspline.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bspline {
    gsl_bspline_workspace *ws;
    gsl_matrix *dB;
	gsl_matrix *dBNonZero;
} bspline_t;

void c_bspline_create(void *handle, double x0, double x1, int32_t degree, int32_t nbreak);
void c_bspline_create_with_breakpoints(void *handle, int32_t degree, double* breakpoints, int N);
void c_bspline_base_eval(const void *handle, int32_t N, const double *xvec, double *BasisVal, double *BasisValD,
                         double *BasisValDD, double *BasisValDDD, double *BasisIntegr);
void c_bspline_base_eval_lee(const void *handle_, int32_t nCoeff, int32_t N, 
                             const double *xvec, double *BasisVal, 
                             double *BasisValDD0,double *BasisValDD1);

void c_bspline_destroy(const void *handle);
void c_bspline_eval(const void *handle, const double *c, double x, double X[3]);
void c_bspline_eval_vec(const void *handle, const double *c, int32_t N, double *xvec, double X[][3]);
int32_t c_bspline_ncoeff(const void *handle);


#ifdef __cplusplus
}
#endif

#endif
/* C_SPLINE_H */
