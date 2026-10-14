#include "PolyUtils.h"
#include <algorithm>

namespace {
    bool badSize(int n) { return n <= 0 || n > POLY_MAX_COEFFS; }
}

extern "C" {

    int PolyAdd(const double* a, int na, const double* b, int nb,
        double* out, int cap) {
        if (!a || !b || !out) return POLY_ERR_NULL;
        if (badSize(na) || badSize(nb)) return POLY_ERR_SIZE;
        int n = std::max(na, nb);
        if (cap < n) return POLY_ERR_BUFFER;
        for (int i = 0; i < n; ++i)
            out[i] = (i < na ? a[i] : 0.0) + (i < nb ? b[i] : 0.0);
        return n;
    }

    int PolyMultiply(const double* a, int na, const double* b, int nb,
        double* out, int cap) {
        if (!a || !b || !out) return POLY_ERR_NULL;
        if (badSize(na) || badSize(nb)) return POLY_ERR_SIZE;
        int n = na + nb - 1;
        if (cap < n) return POLY_ERR_BUFFER;
        std::fill(out, out + n, 0.0);
        for (int i = 0; i < na; ++i)
            for (int j = 0; j < nb; ++j)
                out[i + j] += a[i] * b[j];
        return n;
    }

    int PolyEvaluate(const double* c, int n, double x, double* result) {
        if (!c || !result) return POLY_ERR_NULL;
        if (badSize(n)) return POLY_ERR_SIZE;
        double r = 0.0;                       // схема Горнера
        for (int i = n - 1; i >= 0; --i) r = r * x + c[i];
        *result = r;
        return 0;
    }

    int PolyDerivative(const double* c, int n, double* out, int cap) {
        if (!c || !out) return POLY_ERR_NULL;
        if (badSize(n)) return POLY_ERR_SIZE;
        if (n == 1) {                         // похідна константи = 0
            if (cap < 1) return POLY_ERR_BUFFER;
            out[0] = 0.0;
            return 1;
        }
        if (cap < n - 1) return POLY_ERR_BUFFER;
        for (int i = 1; i < n; ++i) out[i - 1] = i * c[i];
        return n - 1;
    }

    int PolyIntegral(const double* c, int n, double constant, double* out, int cap) {
        if (!c || !out) return POLY_ERR_NULL;
        if (badSize(n)) return POLY_ERR_SIZE;
        if (cap < n + 1) return POLY_ERR_BUFFER;
        out[0] = constant;
        for (int i = 0; i < n; ++i) out[i + 1] = c[i] / (i + 1);
        return n + 1;
    }

} // extern "C"