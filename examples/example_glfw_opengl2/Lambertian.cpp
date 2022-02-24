#include "Lambertian.h"

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const
{
    vec3 s_world = rec.p + rec.normal + random_unit_vector();
    //vec3 s_world = rec.p + rec.normal;
    scattered = Ray(rec.p, s_world - rec.p); //scatteredÎªÉ¢Éä¹âÏß
    attenuation = albedo;
    return true;
}
