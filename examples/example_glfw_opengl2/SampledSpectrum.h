#pragma once
#include <vector>
#include <algorithm>
#include "Spectrum.h"

class xyz3;

// �����������ڴ��ļ���
static const double sampledLambdaStart = 400.0;
static const double sampledLambdaEnd = 700.0;
static const int spectrumSamples = 12;
// POSSIBLE����Spectrumģ�����������ע��include

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
		// ������캯���ᱻ�����inlineʹ�ã�����޷�����ʵ��
		// empty
	}

	xyz3 toXyz3() const;
};

// TIP������ҪΪSampledSpectrum�����һ�����Ը���Ĺ��캯��
inline SampledSpectrum lerp(double t, const SampledSpectrum& s0, const SampledSpectrum& s1) {
	return (1.0 - t) * s0 + t * s1;
}