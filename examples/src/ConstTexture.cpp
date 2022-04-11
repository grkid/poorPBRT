#include "ConstTexture.h"
#include "xyz3.h"
ConstTexture::ConstTexture() {}

ConstTexture::ConstTexture(const rgb3& c)
{
	color = c.toSampledSpectrum();
}

SampledSpectrum ConstTexture::sample(double u, double v, const point3& position) const
{
	return color;
}
