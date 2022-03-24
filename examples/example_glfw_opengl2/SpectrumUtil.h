#pragma once
#include <cfloat>
#include <compare>
#include <vector>
// �ṩһЩ��������Ҫ�Ĺ��з���������

static const int nCIESamples = 471;
extern const double CIE_X[nCIESamples];
extern const double CIE_Y[nCIESamples];
extern const double CIE_Z[nCIESamples];
extern const double CIE_lambda[nCIESamples];

// �����ϵĵ���������Ϣ
struct SpectrumSample
{
	double lambda;	// ����Ƶ��
	double value;	// Ƶ���ϵ�ǿ��

    SpectrumSample(double _lambda, double _value);

	// C++20�����ԣ�lambda��value��˳���ܸı�
	// CUDA��֧��
	auto operator<=>(const SpectrumSample& s1) const = default;
};

double averageSpectrumSamples(std::vector<SpectrumSample> samples, double lambdaBegin, double lambdaEnd);

double utilLerp(double t, double s0, double s1);

double utilClamp(double source, double low = 0.0, double high = DBL_MAX);

std::vector<SpectrumSample> constructSpectrumSamples(const double* lambda, const double* value, const int n);