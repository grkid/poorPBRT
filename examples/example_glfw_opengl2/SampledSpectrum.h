#pragma once
#include <vector>
#include <algorithm>
#include "Spectrum.h"

class xyz3;

// �����������ڴ��ļ���
static const double sampledLambdaStart = 400.0;
static const double sampledLambdaEnd = 750.0;
static const int spectrumSamples = 60;
// POSSIBLE����Spectrumģ�����������ע��include

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
		// ������캯���ᱻ�����inlineʹ�ã�����޷�����ʵ��
		// empty
	}

	xyz3 toXyz3();
};

// TIP������ҪΪSampledSpectrum�����һ�����Ը���Ĺ��캯��
inline SampledSpectrum lerp(double t, const SampledSpectrum& s0, const SampledSpectrum& s1) {
	return (1.0 - t) * s0 + t * s1;
}