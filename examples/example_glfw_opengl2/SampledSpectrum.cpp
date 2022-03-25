#include "SampledSpectrum.h"
#include "xyz3.h"
#include "SpectrumUtil.h"
#include "vec3util.h"

// 类内static私有变量初始化。大坑
SampledSpectrum SampledSpectrum::X;
SampledSpectrum SampledSpectrum::Y;
SampledSpectrum SampledSpectrum::Z;
SampledSpectrum SampledSpectrum::rgbRefl2SpectWhite, SampledSpectrum::rgbRefl2SpectCyan;
SampledSpectrum SampledSpectrum::rgbRefl2SpectMagenta, SampledSpectrum::rgbRefl2SpectYellow;
SampledSpectrum SampledSpectrum::rgbRefl2SpectRed, SampledSpectrum::rgbRefl2SpectGreen;
SampledSpectrum SampledSpectrum::rgbRefl2SpectBlue;
SampledSpectrum SampledSpectrum::rgbIllum2SpectWhite, SampledSpectrum::rgbIllum2SpectCyan;
SampledSpectrum SampledSpectrum::rgbIllum2SpectMagenta, SampledSpectrum::rgbIllum2SpectYellow;
SampledSpectrum SampledSpectrum::rgbIllum2SpectRed, SampledSpectrum::rgbIllum2SpectGreen;
SampledSpectrum SampledSpectrum::rgbIllum2SpectBlue;

void SampledSpectrum::init()
{
    // TODO：可能优化到编译时生成
    auto vecX = constructSpectrumSamples(CIE_lambda, CIE_X, nCIESamples);
    auto vecY = constructSpectrumSamples(CIE_lambda, CIE_Y, nCIESamples);
    auto vecZ = constructSpectrumSamples(CIE_lambda, CIE_Z, nCIESamples);

    X = fromSampled(vecX);
    Y = fromSampled(vecY);
    Z = fromSampled(vecZ);

    auto Refl2SpectWhite = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectWhite, nRGB2SpectSamples);
    auto Refl2SpectCyan = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectCyan, nRGB2SpectSamples);
    auto Refl2SpectMagenta = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectMagenta, nRGB2SpectSamples);
    auto Refl2SpectYellow = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectYellow, nRGB2SpectSamples);
    auto Refl2SpectRed = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectRed, nRGB2SpectSamples);
    auto Refl2SpectGreen = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectGreen, nRGB2SpectSamples);
    auto Refl2SpectBlue = constructSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectBlue, nRGB2SpectSamples);

    rgbRefl2SpectWhite = fromSampled(Refl2SpectWhite);
    rgbRefl2SpectCyan = fromSampled(Refl2SpectCyan);
    rgbRefl2SpectMagenta = fromSampled(Refl2SpectMagenta);
    rgbRefl2SpectYellow = fromSampled(Refl2SpectYellow);
    rgbRefl2SpectRed = fromSampled(Refl2SpectRed);
    rgbRefl2SpectGreen = fromSampled(Refl2SpectGreen);
    rgbRefl2SpectBlue = fromSampled(Refl2SpectBlue);

    auto Illum2SpectWhite = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectWhite, nRGB2SpectSamples);
    auto Illum2SpectCyan = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectCyan, nRGB2SpectSamples);
    auto Illum2SpectMagenta = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectMagenta, nRGB2SpectSamples);
    auto Illum2SpectYellow = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectYellow, nRGB2SpectSamples);
    auto Illum2SpectRed = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectRed, nRGB2SpectSamples);
    auto Illum2SpectGreen = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectGreen, nRGB2SpectSamples);
    auto Illum2SpectBlue = constructSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectBlue, nRGB2SpectSamples);

    rgbIllum2SpectWhite = fromSampled(Illum2SpectWhite);
    rgbIllum2SpectCyan = fromSampled(Illum2SpectCyan);
    rgbIllum2SpectMagenta = fromSampled(Illum2SpectMagenta);
    rgbIllum2SpectYellow = fromSampled(Illum2SpectYellow);
    rgbIllum2SpectRed = fromSampled(Illum2SpectRed);
    rgbIllum2SpectGreen = fromSampled(Illum2SpectGreen);
    rgbIllum2SpectBlue = fromSampled(Illum2SpectBlue);
}

SampledSpectrum SampledSpectrum::fromSampled(std::vector<SpectrumSample> samples)
{
    if(!std::is_sorted(samples.begin(),samples.end()))
	    std::sort(samples.begin(), samples.end());
    SampledSpectrum r(0.0);
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

xyz3 SampledSpectrum::toXyz3() const
{
    xyz3 xyz(0.0, 0.0, 0.0);
    for (int i = 0; i < spectrumSamples; i++) {
        xyz[0] += X[i] * coefficients[i];
        xyz[1] += Y[i] * coefficients[i];
        xyz[2] += Z[i] * coefficients[i];
    }
    double scale = double(sampledLambdaEnd - sampledLambdaStart) / double(CIE_Y_integral * spectrumSamples);
    xyz *= scale;
    return xyz;
}
