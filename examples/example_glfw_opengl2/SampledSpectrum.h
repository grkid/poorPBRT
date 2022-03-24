#pragma once
#include <vector>
#include <algorithm>
#include "Spectrum.h"

class xyz3;

// 作用域限制在此文件中
static const double sampledLambdaStart = 400.0;
static const double sampledLambdaEnd = 750.0;
static const int spectrumSamples = 60;
// POSSIBLE：与Spectrum模板参数重名，注意include

class SampledSpectrum :public Spectrum<spectrumSamples>
{
private:
	static SampledSpectrum X, Y, Z;

public:

	static const int nSpectrumSamples = spectrumSamples;

	static void init();

	static SampledSpectrum fromSampled(std::vector<SpectrumSample> samples);

	SampledSpectrum();

	SampledSpectrum(double initVal);

	SampledSpectrum(const Spectrum<spectrumSamples>& v) 
		:Spectrum<spectrumSamples>(v)
	{
		// 这个构造函数会被下面的inline使用，因此无法分离实现
		// empty
	}

	xyz3 toXyz3();
};

// TIP：必须要为SampledSpectrum类添加一个来自父类的构造函数
inline SampledSpectrum lerp(double t, const SampledSpectrum& s0, const SampledSpectrum& s1) {
	return (1.0 - t) * s0 + t * s1;
}