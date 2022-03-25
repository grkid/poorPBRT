#pragma once
#include <cmath>
#include <cfloat>
#include "SpectrumUtil.h"

template <int spectrumSamples> class Spectrum
{
	// https://pbr-book.org/3ed-2018/Color_and_Radiometry/Spectral_Representation
	// 对应PBRT的CoefficientSpectrum
protected:
	double coefficients[spectrumSamples];	// 光谱

public:

	static const int nSpectrumSamples = spectrumSamples;

	Spectrum() {
		for (int i = 0; i < spectrumSamples; i++) {
			coefficients[i] = 0.0;
		}
	}

	Spectrum(double initVal) {
		for (int i = 0; i < spectrumSamples; i++) {
			coefficients[i] = initVal;
		}
	}

	double& operator[] (int i) {
		// 可选的边界检查
		return coefficients[i];
	}

	Spectrum& operator+=(const Spectrum& s) {
		for (int i = 0; i < spectrumSamples; i++) {
			this->coefficients[i] += s.coefficients[i];
		}
		return *this;
	}

	Spectrum operator+(const Spectrum& s) const{
		Spectrum retVal = *this;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal.coefficients[i] += s.coefficients[i];
		}
		return retVal;
	}

	Spectrum& operator-=(const Spectrum& s) {
		for (int i = 0; i < spectrumSamples; i++) {
			this->coefficients[i] -= s.coefficients[i];
		}
		return *this;
	}

	Spectrum operator-(const Spectrum& s) const{
		Spectrum retVal = *this;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal.coefficients[i] -= s.coefficients[i];
		}
		return retVal;
	}

	Spectrum& operator*=(const Spectrum& s) {
		for (int i = 0; i < spectrumSamples; i++) {
			this->coefficients[i] *= s.coefficients[i];
		}
		return *this;
	}

	Spectrum operator*(const Spectrum& s) const{
		Spectrum retVal = *this;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal.coefficients[i] *= s.coefficients[i];
		}
		return retVal;
	}

	Spectrum& operator/=(const Spectrum& s) {
		for (int i = 0; i < spectrumSamples; i++) {
			this->coefficients[i] /= s.coefficients[i];	// NaN
		}
		return *this;
	}

	Spectrum operator/(const Spectrum& s) const{
		Spectrum retVal = *this;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal.coefficients[i] /= s.coefficients[i];	// NaN
		}
		return retVal;
	}

	Spectrum& operator*=(double s) {
		for (int i = 0; i < spectrumSamples; i++) {
			this->coefficients[i] *= s;
		}
		return *this;
	}

	Spectrum operator*(double s) const{
		Spectrum retVal = *this;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal.coefficients[i] *= s;
		}
		return retVal;
	}

	Spectrum& operator/=(double s) {
		for (int i = 0; i < spectrumSamples; i++) {
			this->coefficients[i] /= s;	// NaN
		}
		return *this;
	}

	Spectrum operator/(double s) const{
		Spectrum retVal = *this;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal.coefficients[i] /= s;	// NaN
		}
		return retVal;
	}

	// C++的友善度
	friend inline Spectrum operator*(double f, const Spectrum& s) {
		return s * f;
	}

	friend inline Spectrum sqrt(const Spectrum& s) {
		Spectrum ret;
		for (int i = 0; i < spectrumSamples; i++)
			ret[i] = std::sqrt(s[i]);
		return ret;
	}

	// 在原PBRT实现中这个方法被特殊处理 TODO
	friend inline Spectrum pow(const Spectrum& s,double e) {
		Spectrum ret;
		for (int i = 0; i < spectrumSamples; i++)
			ret[i] = std::pow(s[i], e);
		return ret;
	}

	friend inline Spectrum exp(const Spectrum& s) {
		Spectrum ret;
		for (int i = 0; i < spectrumSamples; i++)
			ret[i] = std::exp(s[i]);
		return ret;
	}

	bool isBlack() {
		for (int i = 0; i < spectrumSamples; i++) {
			if (coefficients[i] != 0.0) return false;
		}
		return true;
	}

	bool hasNaN() {
		for (int i = 0; i < spectrumSamples; i++)
			if (std::isnan(coefficients[i]))
				return true;
		return false;
	}

	inline Spectrum clamp(double low = 0.0, double high = DBL_MAX) const {
		Spectrum retVal;
		for (int i = 0; i < spectrumSamples; i++) {
			retVal[i] = utilClamp(coefficients[i], low, high);
		}
		return retVal;
	}

	double sum() const{
		double retVal = 0.0;
		for (int i = 0; i < spectrumSamples; i++)
			retVal += coefficients[i];
		return retVal;
	}

	double average() const{
		return sum() / spectrumSamples;
	}
};

template<int spectrumSamples>
inline Spectrum<spectrumSamples> lerp(double t, const Spectrum<spectrumSamples>& s0, const Spectrum<spectrumSamples>& s1) {
	return s0* (1.0 - t)+ s1*t;
}

