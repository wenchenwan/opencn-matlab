#define GSL_DISABLE_DEPRECATED

#include <stddef.h>
#ifdef __KERNEL__
#include <linux/slab.h>
#include <opencn/gsl/gsl_bspline.h>
#include <opencn/ctypes/strings.h>
#else /* __KERNEL__ */
#include <gsl/gsl_bspline.h>
#include <gsl/gsl_multifit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#endif /* __KERNEL__ */

#include "c_spline.h"

static const int nderiv = 3;
static c_bspline_knots (const gsl_vector * breakpts, gsl_bspline_workspace * w);

void c_bspline_create(void *handle_, double x0, double x1, int32_t degree, int32_t nbreak)
{
	size_t* handle = handle_;
    size_t ncoeffs;
    gsl_set_error_handler_off();

#ifdef __KERNEL__
    bspline_t *bs = (bspline_t *)kmalloc(sizeof(bspline_t), GFP_ATOMIC);
#else
    bspline_t *bs = (bspline_t *)malloc(sizeof(bspline_t));
#endif
    bs->ws = gsl_bspline_alloc(degree, nbreak);
    gsl_bspline_knots_uniform(x0, x1, bs->ws);
    
    
    ncoeffs = gsl_bspline_ncoeffs(bs->ws);
    
    // the number of coeffs will not change so we can allocate dB once and forget about it
    bs->dB = gsl_matrix_alloc(ncoeffs, nderiv + 1);
	bs->dBNonZero = gsl_matrix_alloc(degree, nderiv + 1);
    
    *handle = (size_t)bs;
}

void c_bspline_create_with_breakpoints( void *handle_, int32_t degree, double* breakpoints, int N )
{
	size_t* handle = handle_;
    size_t ncoeffs;
    gsl_set_error_handler_off();
#ifdef __KERNEL__
    bspline_t *bs = (bspline_t *)kmalloc(sizeof(bspline_t), GFP_ATOMIC);
#else
    bspline_t *bs = (bspline_t *)malloc(sizeof(bspline_t));
#endif
    
    gsl_vector* brkpnts = gsl_vector_alloc(N);
    for(int i = 0; i < N; i++) {
        gsl_vector_set(brkpnts, i, breakpoints[i]);
    }
    
    bs->ws = gsl_bspline_alloc(degree, N);
    c_bspline_knots(brkpnts, bs->ws);
    
    ncoeffs = gsl_bspline_ncoeffs(bs->ws);
    
    // the number of coeffs will not change so we can allocate dB once and forget about it
    bs->dB = gsl_matrix_alloc(ncoeffs, nderiv + 1);
	bs->dBNonZero = gsl_matrix_alloc(degree, nderiv + 1);
    
    *handle = (size_t)bs;
}

void c_bspline_destroy(const void *handle_)
{
	const size_t* handle = (const size_t*)handle_;
    bspline_t *bs = (bspline_t *)*handle;
    gsl_bspline_free((gsl_bspline_workspace *)bs->ws);
    gsl_matrix_free(bs->dB);
	gsl_matrix_free(bs->dBNonZero);
#ifdef __KERNEL__
    kfree(bs);
#else
    free(bs);
#endif
}

void c_bspline_base_eval(const void *handle_, int32_t N, const double *xvec,
        double *BasisVal, double *BasisValD, double *BasisValDD, double* BasisValDDD,
        double *BasisIntegr)
{
	const size_t* handle = (const size_t*)handle_;
    size_t k, i;
    bspline_t *bs = (bspline_t *)*handle;
    const size_t ncoeffs = gsl_bspline_ncoeffs(bs->ws);
    /* for each sample */
    for (k = 0; k < N; k++) {
        /* for each basis function */
		double x = xvec[k];
		if (x < 0.0) {
			fprintf(stderr, "c_bspline_base_eval: xvec[%lu] = %f, using 0\n", (long unsigned) k, xvec[k]);
			x = 0.0;
		}
		if (x > 1.0) {
			fprintf(stderr, "c_bspline_base_eval: xvec[%lu] = %f, using 1\n", (long unsigned) k, xvec[k]);
			x = 1.0;
		}
		
		// Check for NaN
		if (x != x) {
			fprintf(stderr, "c_bspline_base_eval: xvec[%lu] = %f\n", (long unsigned) k, xvec[k]);
		}

        gsl_bspline_deriv_eval(x, nderiv, bs->dB, bs->ws);
        for (i = 0; i < ncoeffs; i++) {
            BasisVal[i * N + k] = gsl_matrix_get(bs->dB, i, 0);
            BasisValD[i * N + k] = gsl_matrix_get(bs->dB, i, 1);
            BasisValDD[i * N + k] = gsl_matrix_get(bs->dB, i, 2);
        }
    }
    
    for (i = 0; i < ncoeffs; i++) {
        BasisIntegr[i] = 0.0;
        for (k = 0; k < N; k++) {
            BasisIntegr[i] += BasisVal[i * N + k];
        }
    }
}

void c_bspline_eval(const void *handle_, const double *c, double x, double X[4])
{
	const size_t* handle = (const size_t*)handle_;
    size_t k, i, istart, iend;
    bspline_t *bs = (bspline_t *)*handle;
    
#ifdef __KERNEL__
    if (x < 0.0) {
        opencn_cprintf(OPENCN_COLOR_BRED, "c_bspline_eval: x < 0\n");
        x = 0.0;
    }
    if (x > 1.0) {
        opencn_cprintf(OPENCN_COLOR_BRED, "c_bspline_eval: x > 1\n");
        x = 1.0;
    }
#else
    if (x < 0.0) {
        fprintf(stderr, "c_bspline_eval: x < 0\n");
        x = 0.0;
    }
    if (x > 1.0) {
        fprintf(stderr, "c_bspline_eval: x > 1\n");
        x = 1.0;
    }
	// Check for NaN
	if (x != x) {
		fprintf(stderr, "c_bspline_eval: x = %f\n", x);
	}
#endif
   
    gsl_bspline_deriv_eval_nonzero(x, nderiv, bs->dBNonZero, &istart, &iend, bs->ws);
    /* for each deriv degree */
    for (k = 0; k < nderiv + 1; k++) {
        X[k] = 0.0;
        /* for each coeff */
        for (i = istart; i <= iend; i++) {
            X[k] += gsl_matrix_get(bs->dBNonZero, i - istart, k) * c[i];
        }
    }
}

void c_bspline_eval_vec(const void *handle_, const double *c, int32_t N, double *xvec,
        double X[][3])
{
	const size_t* handle = (const size_t*)handle_;
    size_t i;
    /* for each sample */
    for (i = 0; i < N; i++) {
        c_bspline_eval(handle, c, xvec[i], (double *)&X[i]);
    }
}

gsl_vector *zeros(size_t n)
{
    gsl_vector *v = gsl_vector_alloc(n);
    gsl_vector_set_zero(v);
    return v;
}

int32_t c_bspline_ncoeff(const void *handle_)
{
	const size_t* handle = (const size_t*)handle_;
    bspline_t *bs = (bspline_t *)*handle;
    return gsl_bspline_ncoeffs(bs->ws);
}

/*
    c_bspline_knots()
      Compute the knots from the given breakpoints:
       knots(1:k) = breakpts(1)
       knots(k+1:k+l-1) = breakpts(i), i = 2 .. l
       knots(n+1:n+k) = breakpts(l + 1)
    where l is the number of polynomial pieces (l = nbreak - 1) and
       n = k + l - 1
    (using matlab syntax for the arrays)
    The repeated knots at the beginning and end of the interval
    correspond to the continuity condition there. See pg. 119
    of [1].
    Inputs: breakpts - breakpoints
            w        - bspline workspace
    Return: success or error
*/
int
c_bspline_knots (const gsl_vector * breakpts, gsl_bspline_workspace * w)
{
  if (breakpts->size != w->nbreak)
    {
      GSL_ERROR ("breakpts vector has wrong size", GSL_EBADLEN);
    }
  else
    {
      size_t i; /* looping */

      for (i = 0; i < w->k; i++)
        gsl_vector_set (w->knots, i, gsl_vector_get (breakpts, 0));

      for (i = 1; i < w->l; i++)
        {
          gsl_vector_set (w->knots, w->k - 1 + i,
          gsl_vector_get (breakpts, i));
        }

      for (i = w->n; i < w->n + w->k; i++)
        gsl_vector_set (w->knots, i, gsl_vector_get (breakpts, w->l));

      return GSL_SUCCESS;
    }
} /* c_bspline_knots() */

