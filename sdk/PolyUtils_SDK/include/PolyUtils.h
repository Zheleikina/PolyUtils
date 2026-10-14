#pragma once

#if defined(POLYUTILS_STATIC)
#define POLY_API
#elif defined(POLYUTILS_EXPORTS)
#define POLY_API __declspec(dllexport)
#else
#define POLY_API __declspec(dllimport)
#endif

#define POLY_ERR_NULL    (-1)  /* nullptr замість обов'язкового вказівника */
#define POLY_ERR_SIZE    (-2)  /* n <= 0 або n > POLY_MAX_COEFFS */
#define POLY_ERR_BUFFER  (-3)  /* буфер результату замалий */
#define POLY_MAX_COEFFS  10000

#ifdef __cplusplus
extern "C" {
#endif

    POLY_API int PolyAdd(const double* a, int na, const double* b, int nb,
        double* out, int outCapacity);
    POLY_API int PolyMultiply(const double* a, int na, const double* b, int nb,
        double* out, int outCapacity);
    POLY_API int PolyEvaluate(const double* coeffs, int n, double x, double* result);
    POLY_API int PolyDerivative(const double* coeffs, int n,
        double* out, int outCapacity);
    POLY_API int PolyIntegral(const double* coeffs, int n, double constant,
        double* out, int outCapacity);

#ifdef __cplusplus
}
#endif