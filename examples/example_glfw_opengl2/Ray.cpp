#include "Ray.h"

Ray::Ray(const vec3& a, const vec3& b,double t)
{
    A = a;
    B = b;
    tm = t;
}
vec3 Ray::origin() const { return A; }
vec3 Ray::direction() const { return B; }
vec3 Ray::point_at_parameter(double t) const { return A + t * B; } //ÖÕµãµÄ×ø±ê
double Ray::time() const { return tm; }