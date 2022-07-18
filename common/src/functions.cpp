#include "queue_coder.h"


void c_opt_geom(double *X, double *Y) {}
void c_roots(double *coeffs, creal_T *roots, int n) {
    double *roots_as_double = (double *)roots;
    gsl_poly_complex_workspace *ws = gsl_poly_complex_workspace_alloc(n);
    int status = gsl_poly_complex_solve(coeffs, n, ws, roots_as_double);
	if (status != GSL_SUCCESS) {
		fprintf(stderr, "c_roots: poly_complex_solve failed\n");
	}
    gsl_poly_complex_workspace_free(ws);
}

/*void linspace(double *out, double x0, double x1, int n) {
    int i;
    for (i = 0; i < n; i++) {
        out[i] = x0 + (x1 - x0) / (n - 1) * i;
    }
}
*/



void c_assert_(const char *msg) {
    fprintf(stderr, "(c_assert) %s\n", msg);
#warning TEMPORARY ASSERT
    assert(false);
}



#ifdef __cplusplus
#include <vector>
#include <iostream>

// #include "rs274dev.h"
// #include "rs274ngc_interp.hh"
// #include "rs274ngc_return.hh"
// 
// 
// namespace {
//     Interp interp;
//     ocn::CurvStruct Curv;
// }

// void push_curv_struct(const ocn::CurvStruct *c) {
//     Curv = *c;
// }
// 
// int c_open_gcode(const char* filename, ocn::CurvStruct*)
// {
//     if (interp.init() != INTERP_OK) {
//         fprintf(stderr, "Failed to init interp\n");
//         return 0;
//     }
//     if (interp.open(filename) != INTERP_OK) {
//         fprintf(stderr, "Failed to open file '%s'\n", filename);
//         return 0;
//     }
// 
//     interp.set_loglevel(0);
// 
//     interp.execute("G10 L2 P1 X0 Y0 Z0");
//     interp.synch();
// 
//     return 1;
// }
// 
// 
// int c_read_and_exec_gcode(const char *, ocn::CurvStruct *value)
// {
//     Curv.Info.Type = ocn::CurveType_None;
//     int status = INTERP_OK;
//     status = interp.read();
//     
//     if (status == INTERP_ENDFILE) {
//         return 1;
//     }
//     if ((status != INTERP_OK) &&
//         (status != INTERP_EXECUTE_FINISH)) {
//         
//         std::cout << "\033[1;31m[ERROR]\033[0m"<< " Reading line " 
//                 << interp.line() << " : " << interp.getSavedError() << std::endl;
//         return 0;
//     }
// 
//     status = interp.execute();
// 
//     if ((status != INTERP_OK) &&
//         (status != INTERP_EXIT) &&
//         (status != INTERP_EXECUTE_FINISH)) {
//         std::cout << "\033[1;31m[ERROR]\033[0m" << " Executing line " 
//                 << interp.line() << " : " << interp.getSavedError() << std::endl;
//         return 0;
//     } else if (status == INTERP_EXIT) {
//         return 1;
//     }
// 
//     *value = Curv;
//     return 1;
// }

using CurveVector = std::vector<ocn::CurvStruct>;


#ifdef OPENCN_32_BITS

ocn::uint64m_T c_queue_new()
{
    ocn::uint64m_T ptr;
    CurveVector *curv =  new CurveVector();

    ptr.chunks[0] = reinterpret_cast<unsigned int>(curv);

    return ptr;
}

void c_queue_get(ocn::uint64m_T ptr, int32_t index, ocn::CurvStruct *value)
{
    auto q = reinterpret_cast<CurveVector*>(ptr.chunks[0]);
    *value = q->at(index - 1);
}

void c_queue_set(ocn::uint64m_T ptr, int32_t index, ocn::CurvStruct value)
{
    auto q = reinterpret_cast<CurveVector*>(ptr.chunks[0]);
    q->at(index - 1) = value;
}

int32_t c_queue_size(ocn::uint64m_T ptr)
{
    auto q = reinterpret_cast<CurveVector*>(ptr.chunks[0]);
    return q->size();
}

void c_queue_push(ocn::uint64m_T ptr, ocn::CurvStruct value)
{
    auto q = reinterpret_cast<CurveVector*>(ptr.chunks[0]);
    q->push_back(value);
}

#else /* ndef OPENCN_32_BITS */

uint64_t c_queue_new()
{
    return reinterpret_cast<uint64_t>(new CurveVector());
}

void c_queue_get(uint64_t ptr, int32_t index, ocn::CurvStruct *value)
{
    auto q = reinterpret_cast<CurveVector*>(ptr);
    *value = q->at(index - 1);
}

void c_queue_set(uint64_t ptr, int32_t index, ocn::CurvStruct value)
{
    auto q = reinterpret_cast<CurveVector*>(ptr);
    q->at(index - 1) = value;
}

int32_t c_queue_size(uint64_t ptr)
{
    auto q = reinterpret_cast<CurveVector*>(ptr);
    return q->size();
}

void c_queue_push(uint64_t ptr, ocn::CurvStruct value)
{
    auto q = reinterpret_cast<CurveVector*>(ptr);
    q->push_back(value);
}


#endif /* else */



#endif



