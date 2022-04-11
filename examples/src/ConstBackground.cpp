#include "ConstBackground.h"
#include "xyz3.h"
ConstBackground::ConstBackground(const rgb3& color)
{
	baseColor = color.toSampledSpectrum(SpectrumType::illuminant);
}

SampledSpectrum ConstBackground::sample(const Ray& ray) const
{
	return baseColor;
}
