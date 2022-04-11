#include "Principled.h"
#include "ConstTexture.h"
#include "HitRecord.h"
#include "xyz3.h"

// 原shader中的函数，不允许外部调用

inline static double sqr(double x) { return x * x; }

inline static double SchlickFresnel(double u)
{
	double m = utilClamp(1 - u, 0, 1);
	double m2 = m * m;
	return m2 * m2 * m; // pow(m,5)
}

inline static double GTR1(double NdotH, double a)
{
	if (a >= 1) return 1 / M_PI;
	double a2 = a * a;
	double t = 1 + (a2 - 1) * NdotH * NdotH;
	return (a2 - 1) / (M_PI * log(a2) * t);
}

inline static double GTR2(double NdotH, double a)
{
	double a2 = a * a;
	double t = 1 + (a2 - 1) * NdotH * NdotH;
	return a2 / (M_PI * t * t);
}

inline static double GTR2_aniso(double NdotH, double HdotX, double HdotY, double ax, double ay)
{
	return 1 / (M_PI * ax * ay * sqr(sqr(HdotX / ax) + sqr(HdotY / ay) + NdotH * NdotH));
}

inline static double smithG_GGX(double NdotV, double alphaG)
{
	double a = alphaG * alphaG;
	double b = NdotV * NdotV;
	return 1 / (NdotV + sqrt(a + b - a * b));
}

inline static double smithG_GGX_aniso(double NdotV, double VdotX, double VdotY, double ax, double ay)
{
	return 1 / (NdotV + sqrt(sqr(VdotX * ax) + sqr(VdotY * ay) + sqr(NdotV)));
}

inline static rgb3 mon2lin(rgb3 x)
{
	return rgb3(pow(x[0], 2.2), pow(x[1], 2.2), pow(x[2], 2.2));
}

inline static rgb3 mix(rgb3 a, rgb3 b, double r) 
{
	return (1.0 - r) * a + r * b;
}

inline static double mix(double a, double b, double r)
{
	return (1.0 - r) * a + r * b;
}

Principled::Principled()
{
	baseColor = std::make_shared<ConstTexture>(defaultBaseColor);
}

Principled::Principled(std::shared_ptr<Texture> _baseColor, 
	std::optional<double> _subSurface, std::optional<double> _metallic, 
	std::optional<double> _specular, std::optional<double> _specularTint, 
	std::optional<double> _roughness, std::optional<double> _anisotropic, 
	std::optional<double> _sheen, std::optional<double> _sheenTint, 
	std::optional<double> _clearCoat, std::optional<double> _clearCoatGloss)
{
	setBaseColor(_baseColor);
	if (_subSurface.has_value())
		setSubSurface(_subSurface.value());
	if (_metallic.has_value())
		setMetallic(_metallic.value());
	if (_specular.has_value())
		setSpecular(_specular.value());
	if (_specularTint.has_value())
		setSpecularTint(_specularTint.value());
	if (_roughness.has_value())
		setRoughness(_roughness.value());
	if (_anisotropic.has_value())
		setAnisotropic(_anisotropic.value());
	if (_sheen.has_value())
		setSheen(_sheen.value());
	if (_sheenTint.has_value())
		setSheenTint(_sheenTint.value());
	if (_clearCoat.has_value())
		setClearCoat(_clearCoat.value());
	if (_clearCoatGloss.has_value())
		setClearCoatGloss(_clearCoatGloss.value());
}

Principled::Principled(const rgb3& _baseColor,
	std::optional<double> _subSurface, std::optional<double> _metallic,
	std::optional<double> _specular, std::optional<double> _specularTint,
	std::optional<double> _roughness, std::optional<double> _anisotropic,
	std::optional<double> _sheen, std::optional<double> _sheenTint,
	std::optional<double> _clearCoat, std::optional<double> _clearCoatGloss)
{
	setBaseColor(_baseColor);
	if (_subSurface.has_value())
		setSubSurface(_subSurface.value());
	if (_metallic.has_value())
		setMetallic(_metallic.value());
	if (_specular.has_value())
		setSpecular(_specular.value());
	if (_specularTint.has_value())
		setSpecularTint(_specularTint.value());
	if (_roughness.has_value())
		setRoughness(_roughness.value());
	if (_anisotropic.has_value())
		setAnisotropic(_anisotropic.value());
	if (_sheen.has_value())
		setSheen(_sheen.value());
	if (_sheenTint.has_value())
		setSheenTint(_sheenTint.value());
	if (_clearCoat.has_value())
		setClearCoat(_clearCoat.value());
	if (_clearCoatGloss.has_value())
		setClearCoatGloss(_clearCoatGloss.value());
}

void Principled::setBaseColor(std::shared_ptr<Texture> newBaseColor)
{
	baseColor = newBaseColor;
}
void Principled::setBaseColor(const rgb3& newBaseColor)
{
	baseColor = std::make_shared<ConstTexture>(newBaseColor);
}
std::shared_ptr<Texture> Principled::getBaseColor()
{
	return baseColor;
}
void Principled::setSubSurface(double in)
{
	subSurface = in;
}
double Principled::getSubSurface()
{
	return subSurface;
}
void Principled::setMetallic(double in)
{
	metallic = in;
}
double Principled::getMetallic()
{
	return metallic;
}
void Principled::setSpecular(double in)
{
	specular = in;
}
double Principled::getSpecular()
{
	return specular;
}
void Principled::setSpecularTint(double in)
{
	specularTint = in;
}
double Principled::getSpecularTint()
{
	return specularTint;
}
void Principled::setRoughness(double in)
{
	roughness = in;
}
double Principled::getRoughness()
{
	return roughness;
}
void Principled::setAnisotropic(double in)
{
	anisotropic = in;
}
double Principled::getAnisotropic()
{
	return anisotropic;
}
void Principled::setSheen(double in)
{
	sheen = in;
}
double Principled::getSheen()
{
	return sheen;
}
void Principled::setSheenTint(double in)
{
	sheenTint = in;
}
double Principled::getSheenTint()
{
	return sheenTint;
}
void Principled::setClearCoat(double in)
{
	clearCoat = in;
}
double Principled::getClearCoat()
{
	return clearCoat;
}
void Principled::setClearCoatGloss(double in)
{
	clearCoatGloss = in;
}
double Principled::getClearCoatGloss()
{
	return clearCoatGloss;
}

bool Principled::scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const
{
	return false;
}
