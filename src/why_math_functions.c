#include "why_math.h"
#include "why_math_complex.h"

#include <math.h>

Complex math_id(Complex z)
{
    return z;
}

Complex math_sin(Complex z)
{
    return (Complex){sin(z.re), 0};
}

Complex math_cos(Complex z)
{
    return complex(cos(z.re), 0);
}

Complex math_tan(Complex z)
{
    return complex(tan(z.re), 0);
}

Complex math_log(Complex z)
{
    return complex(log2(z.re), 0);
}