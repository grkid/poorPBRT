#include "InitBackground.h"

vec3 InitBackground::sample(const Ray& ray) const
{
    vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
