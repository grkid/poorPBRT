#pragma once
#include <cfloat>
#include <compare>
#include <vector>
// 提供一些光谱类需要的公有方法和类型

static const int nCIESamples = 471;
static const double CIE_Y_integral = 106.856895;	// ? 没有理解其意义
extern const double CIE_X[nCIESamples];
extern const double CIE_Y[nCIESamples];
extern const double CIE_Z[nCIESamples];
extern const double CIE_lambda[nCIESamples];

static const int nRGB2SpectSamples = 32;
extern const double RGB2SpectLambda[nRGB2SpectSamples];
extern const double RGBRefl2SpectWhite[nRGB2SpectSamples];
extern const double RGBRefl2SpectCyan[nRGB2SpectSamples];
extern const double RGBRefl2SpectMagenta[nRGB2SpectSamples];
extern const double RGBRefl2SpectYellow[nRGB2SpectSamples];
extern const double RGBRefl2SpectRed[nRGB2SpectSamples];
extern const double RGBRefl2SpectGreen[nRGB2SpectSamples];
extern const double RGBRefl2SpectBlue[nRGB2SpectSamples];
extern const double RGBIllum2SpectWhite[nRGB2SpectSamples];
extern const double RGBIllum2SpectCyan[nRGB2SpectSamples];
extern const double RGBIllum2SpectMagenta[nRGB2SpectSamples];
extern const double RGBIllum2SpectYellow[nRGB2SpectSamples];
extern const double RGBIllum2SpectRed[nRGB2SpectSamples];
extern const double RGBIllum2SpectGreen[nRGB2SpectSamples];
extern const double RGBIllum2SpectBlue[nRGB2SpectSamples];

// 光谱上的单个采样信息
struct SpectrumSample
{
	double lambda;	// 光谱频率
	double value;	// 频率上的强度

    SpectrumSample(double _lambda, double _value);

	// C++20新特性，lambda和value的顺序不能改变
	// CUDA不支持
	auto operator<=>(const SpectrumSample& s1) const = default;
};

double averageSpectrumSamples(std::vector<SpectrumSample> samples, double lambdaBegin, double lambdaEnd);

double utilLerp(double t, double s0, double s1);

double utilClamp(double source, double low = 0.0, double high = DBL_MAX);

std::vector<SpectrumSample> constructSpectrumSamples(const double* lambda, const double* value, const int n);