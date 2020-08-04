#ifndef C_FUNCTIONS_H
#define C_FUNCTIONS_H

#include "c_spline.h"

#include <matlab_headers.h>

#ifdef __KERNEL__
#error "This should not be used in the kernel"
#else
#include <stdio.h>
#include <gsl/gsl_poly.h>
#include <assert.h>
#include "sinspace.h"
#endif

#if defined(MATLAB_MEX_FILE)
#include "../gen_mex/readgcode/ReadGCode_mex_types.h"
#endif



void c_opt_geom(double *X, double *Y);
void c_roots(double *coeffs, creal_T *roots, int n);
void c_assert_(const char *msg);

#ifdef OPENCN_32_BITS
ocn::uint64m_T c_queue_new();
void c_queue_get(ocn::uint64m_T ptr, int32_t index, ocn::CurvStruct* value);
void c_queue_set(ocn::uint64m_T ptr, int32_t index, ocn::CurvStruct value);
void c_queue_push(ocn::uint64m_T ptr, ocn::CurvStruct value);
int32_t c_queue_size(ocn::uint64m_T ptr);
#else
uint64_t c_queue_new();
void c_queue_get(uint64_t ptr, int32_t index, ocn::CurvStruct* value);
void c_queue_set(uint64_t ptr, int32_t index, ocn::CurvStruct value);
void c_queue_push(uint64_t ptr, ocn::CurvStruct value);
int32_t c_queue_size(uint64_t ptr);
#endif

/* void linspace(double *out, double x0, double x1, int n); */


int c_open_gcode(const char*filename, ocn::CurvStruct*);
int c_read_and_exec_gcode(const char*, ocn::CurvStruct* value);

#endif
