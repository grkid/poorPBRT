#include "Metal.h"

Metal::Metal(const vec3& a, double f) : albedo(a)
{
    fuzz = f < 1 ? f : 1;
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const
{
    vec3 v = unit_vector(r_in.direction());
    vec3 n = rec.normal;
    vec3 p = rec.p;
    vec3 r = reflect(v, n);
    vec3 offset = fuzz * random_unit_vector();
    scattered = Ray(p, r + offset);
    //scattered = Ray(p, r);

    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
