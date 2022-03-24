#include "SampledSpectrum.h"
#include "xyz3.h"
#include "SpectrumUtil.h"

// 类内static私有变量初始化。大坑
SampledSpectrum SampledSpectrum::X;
SampledSpectrum SampledSpectrum::Y;
SampledSpectrum SampledSpectrum::Z;

void SampledSpectrum::init()
{
    // TODO：可能优化到编译时生成
    auto vecX = constructSpectrumSamples(CIE_lambda, CIE_X, nCIESamples);
    auto vecY = constructSpectrumSamples(CIE_lambda, CIE_Y, nCIESamples);
    auto vecZ = constructSpectrumSamples(CIE_lambda, CIE_Z, nCIESamples);

    SampledSpectrum::X = fromSampled(vecX);
    SampledSpectrum::Y = fromSampled(vecY);
    SampledSpectrum::Z = fromSampled(vecZ);
}

SampledSpectrum SampledSpectrum::fromSampled(std::vector<SpectrumSample> samples)
{
    if(!std::is_sorted(samples.begin(),samples.end()))
	    std::sort(samples.begin(), samples.end());
    SampledSpectrum r;
    for (int i = 0; i < spectrumSamples; i++) {
        double lambda0 = utilLerp(double(i) / double(spectrumSamples), sampledLambdaStart, sampledLambdaEnd);
        double lambda1= utilLerp(double(i+1) / double(spectrumSamples), sampledLambdaStart, sampledLambdaEnd);
        r[i] = averageSpectrumSamples(samples, lambda0, lambda1);
    }
    return r;
}

SampledSpectrum::SampledSpectrum()
	:Spectrum()
{
	// empty
}

SampledSpectrum::SampledSpectrum(double initVal)
	:Spectrum(initVal)
{
	// empty
}

xyz3 SampledSpectrum::toXyz3()
{
    return xyz3();
}
