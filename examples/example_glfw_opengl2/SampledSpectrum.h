#pragma once
#include "Spectrum.h"

// 作用域限制在此文件中
static const double sampledLambdaStart = 400.0;
static const double sampledLambdaEnd = 750.0;
static const int spectrumSamples = 60;

class SampledSpectrum :public Spectrum<spectrumSamples>
{
public:
	SampledSpectrum();
	SampledSpectrum(double initVal);
	SampledSpectrum(const Spectrum<spectrumSamples>& v) 
		:Spectrum<spectrumSamples>(v)
	{
		// 这个构造函数会被下面的inline使用，因此无法分离实现
		// empty
	}
};

// TIP：必须要为SampledSpectrum类添加一个来自父类的构造函数
inline SampledSpectrum lerp(double t, const SampledSpectrum& s0, const SampledSpectrum& s1) {
	return (1.0 - t) * s0 + t * s1;
}