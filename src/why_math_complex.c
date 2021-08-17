#include "why_math_complex.h"
#include "why_math.h"
#include "why_macros.h"

#include <assert.h>

Complex complex(real re, real im)
{
    return (Complex){re, im};
}

Complex complex_zero()
{
    return (Complex){0, 0};
}

boolean complex_is_real(Complex z)
{
    return z.im == 0 ? TRUE : FALSE;
}

boolean complex_is_zero(Complex z)
{
    return (z.re == 0 && z.im == 0) ? TRUE : FALSE;
}

Complex complex_conjugate(Complex z)
{
    return (Complex){z.re, -z.im};
}

Complex complex_add(Complex lhs, Complex rhs)
{
    return (Complex){lhs.re + rhs.re, lhs.im + rhs.im};
}

Complex complex_mult(Complex lhs, Complex rhs)
{
    return (Complex){lhs.re * rhs.re - lhs.im * rhs.im, lhs.im * rhs.re + lhs.re * rhs.im};
}

Complex complex_scale(Complex z, real a)
{
    return (Complex){z.re * a, z.im * a};
}

real complex_mod_squared(Complex z)
{
    return z.re * z.re + z.im * z.im;
}

Complex complex_inv(Complex z)
{
    if (complex_is_zero(z))
        assert(0);
    
    return (Complex){z.re / complex_mod_squared(z), -z.im / complex_mod_squared(z)};
}

Complex complex_div(Complex lhs, Complex rhs)
{
    return complex_mult(lhs, complex_inv(rhs));
}