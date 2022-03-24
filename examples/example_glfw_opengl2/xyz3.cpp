#include "xyz3.h"
#include "rgb3.h"
#include "SampledSpectrum.h"

rgb3 xyz3::toRgb3()
{
	rgb3 rgb;
	rgb[0] = 3.240479f * e[0] - 1.537150f * e[1] - 0.498535f * e[2];
	rgb[1] = -0.969256f * e[0] + 1.875991f * e[1] + 0.041556f * e[2];
	rgb[2] = 0.055648f * e[0] - 0.204043f * e[1] + 1.057311f * e[2];
	return rgb;
}

SampledSpectrum xyz3::toSampledSpectrum()
{
	return SampledSpectrum();
}
