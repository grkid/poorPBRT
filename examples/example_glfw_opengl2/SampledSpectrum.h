#pragma once
#include "Spectrum.h"

// �����������ڴ��ļ���
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
		// ������캯���ᱻ�����inlineʹ�ã�����޷�����ʵ��
		// empty
	}
};

// TIP������ҪΪSampledSpectrum�����һ�����Ը���Ĺ��캯��
inline SampledSpectrum lerp(double t, const SampledSpectrum& s0, const SampledSpectrum& s1) {
	return (1.0 - t) * s0 + t * s1;
}