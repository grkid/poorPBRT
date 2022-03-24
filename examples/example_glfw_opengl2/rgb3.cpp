#include "rgb3.h"
#include "xyz3.h"
#include "SampledSpectrum.h"

xyz3 rgb3::toXyz3()
{   
    xyz3 xyz;
    xyz[0] = 0.412453f * e[0] + 0.357580f * e[1] + 0.180423f * e[2];
    xyz[1] = 0.212671f * e[0] + 0.715160f * e[1] + 0.072169f * e[2];
    xyz[2] = 0.019334f * e[0] + 0.119193f * e[1] + 0.950227f * e[2];
    return xyz;
}
