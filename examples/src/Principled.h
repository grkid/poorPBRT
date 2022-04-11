#pragma once
#include <optional>
#include "Material.h"
#include "Texture.h"

// Disney Principled PBR BRDF
// https://github.com/wdas/brdf/blob/main/src/brdfs/disney.brdf
class Principled :
    public Material
{
private:
    const rgb3 defaultBaseColor = rgb3(0.8, 0.8, 0.8);
    std::shared_ptr<Texture> baseColor;
    double subSurface = 0.0; double metallic = 0.0;
    double specular = 0.5; double specularTint = 0.0;
    double roughness = 0.4; double anisotropic = 0.0;
    double sheen = 0.0; double sheenTint = 0.0;
    double clearCoat = 0.0; double clearCoatGloss = 0.0;

public:

    Principled();

    Principled(std::shared_ptr<Texture> _baseColor, 
        std::optional<double> _subSurface, std::optional<double> _metallic,
        std::optional<double> _specular, std::optional<double> _specularTint,
        std::optional<double> _roughness, std::optional<double> _anisotropic,
        std::optional<double> _sheen, std::optional<double> _sheenTint,
        std::optional<double> _clearCoat, std::optional<double> _clearCoatGloss);

    Principled(const rgb3& baseColor,
        std::optional<double> _subSurface, std::optional<double> _metallic,
        std::optional<double> _specular, std::optional<double> _specularTint,
        std::optional<double> _roughness, std::optional<double> _anisotropic,
        std::optional<double> _sheen, std::optional<double> _sheenTint,
        std::optional<double> _clearCoat, std::optional<double> _clearCoatGloss);

    void setBaseColor(std::shared_ptr<Texture> newBaseColor);
    void setBaseColor(const rgb3& newBaseColor);
    std::shared_ptr<Texture> getBaseColor();

    void setSubSurface(double in);
    double getSubSurface();

    void setMetallic(double in);
    double getMetallic();

    void setSpecular(double in);
    double getSpecular();

    void setSpecularTint(double in);
    double getSpecularTint();

    void setRoughness(double in);
    double getRoughness();

    void setAnisotropic(double in);
    double getAnisotropic();

    void setSheen(double in);
    double getSheen();

    void setSheenTint(double in);
    double getSheenTint();

    void setClearCoat(double in);
    double getClearCoat();

    void setClearCoatGloss(double in);
    double getClearCoatGloss();

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const;
};

