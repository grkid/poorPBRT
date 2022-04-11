#include "Lambertian.h"

Lambertian::Lambertian(std::shared_ptr<Texture> b) : baseColor(b) {}

Lambertian::Lambertian(const rgb3& v)
{
    baseColor = std::make_shared<ConstTexture>(v);
}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const
{
    vec3 s_world = rec.p + rec.normal + random_unit_vector();
    //vec3 s_world = rec.p + rec.normal;
    scattered = Ray(rec.p, s_world - rec.p,r_in.time()); //scatteredÎªÉ¢Éä¹âÏß
    attenuation = baseColor->sample(rec.u, rec.v, rec.p);
    return true;
}
