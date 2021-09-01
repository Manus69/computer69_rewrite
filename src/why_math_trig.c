#include "why_math.h"

#include <assert.h>

#define TRIG_DELTA 1.0 / (1 << 12)
#define TWO_PI 2 * PI
#define C_SIZE 12

//maps angle closer to the origin and adjusts its sign
static real _map_angle_sin(real x)
{
    if (x < PI / 2)
        return x;
    
    if (x < PI)
        return PI - x;
    
    if (x < 3 * PI / 2)
        return PI - x;
    
    return x - 2 * PI;
}

static real _sin_coefficients[C_SIZE] = {0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1};

//sin x = 0 + x + 0x^2 - x^3/3! + 0x^4 + x^5/5! + 0x^6 - x^7/7!
real math_sin(real x)
{
    int_signed n;
    real result;

    x = math_mod(x, TWO_PI);
    x = _map_angle_sin(x);

    n = C_SIZE - 1;
    result = 0;
    while (n > 0)
    {
        result += _sin_coefficients[n];
        result = (result * x) / n;

        n --;
    }

    result += _sin_coefficients[0];

    return result;
}

real math_cos(real x)
{
    return math_sin(x + PI / 2);
}

real math_tan(real x)
{
    x = math_mod(x, TWO_PI);

    if (within_delta(x, PI / 2, TRIG_DELTA))
        assert(0);

    if (within_delta(x, 3 * PI / 2, TRIG_DELTA))
        assert(0);
    
    return math_sin(x) / math_cos(x);
}
