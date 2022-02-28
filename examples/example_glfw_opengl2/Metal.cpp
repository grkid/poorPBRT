#include "Metal.h"

Metal::Metal(std::shared_ptr<Texture> b, double f) : baseColor(b)
{
    fuzz = f < 1 ? f : 1;
}

Metal::Metal(const vec3& v, double f)
{
    baseColor = std::make_shared<ConstTexture>(v);
    fuzz = f;
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const
{
    vec3 v = unit_vector(r_in.direction());
    vec3 n = rec.normal;
    vec3 p = rec.p;
    vec3 r = reflect(v, n);
    vec3 offset = fuzz * random_unit_vector();
    scattered = Ray(p, r + offset,r_in.time());
    //scattered = Ray(p, r);

    attenuation = baseColor->sample(rec.u, rec.v, rec.p);
    return (dot(scattered.direction(), rec.normal) > 0);
}
