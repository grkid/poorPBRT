#pragma once
#include "vec3.h"
// ??Spectrum?Խ?
class rgb3;
class SampledSpectrum;
class xyz3:public vec3
{
public:
	xyz3() :vec3() {}
	xyz3(double e0, double e1, double e2) :vec3(e0, e1, e2) {};
	xyz3(vec3 v) :vec3(v) {};

	rgb3 toRgb3() const;
	/*SampledSpectrum toSampledSpectrum() const;*/
};