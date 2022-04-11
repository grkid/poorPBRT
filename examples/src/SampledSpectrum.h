#pragma once
#include <vector>
#include <algorithm>
#include "Spectrum.h"

class xyz3;

// 作用域限制在此文件中
static const double sampledLambdaStart = 400.0;
static const double sampledLambdaEnd = 700.0;
static const int spectrumSamples = 12;
// POSSIBLE：与Spectrum模板参数重名，注意include

enum class SpectrumType { reflectance, illuminant };

class SampledSpectrum :public Spectrum<spectrumSamples>
{
private:

	static SampledSpectrum X, Y, Z;
	static SampledSpectrum rgbRefl2SpectWhite, rgbRefl2SpectCyan;
	static SampledSpectrum rgbRefl2SpectMagenta, rgbRefl2SpectYellow;
	static SampledSpectrum rgbRefl2SpectRed, rgbRefl2SpectGreen;
	static SampledSpectrum rgbRefl2SpectBlue;
	static SampledSpectrum rgbIllum2SpectWhite, rgbIllum2SpectCyan;
	static SampledSpectrum rgbIllum2SpectMagenta, rgbIllum2SpectYellow;
	static SampledSpectrum rgbIllum2SpectRed, rgbIllum2SpectGreen;
	static SampledSpectrum rgbIllum2SpectBlue;

public:

	friend class xyz3;
	friend class rgb3;

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

	xyz3 toXyz3() const;
};

// TIP：必须要为SampledSpectrum类添加一个来自父类的构造函数
inline SampledSpectrum lerp(double t, const SampledSpectrum& s0, const SampledSpectrum& s1) {
	return (1.0 - t) * s0 + t * s1;
}