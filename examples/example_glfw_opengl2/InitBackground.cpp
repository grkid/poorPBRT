#include "InitBackground.h"

rgb3 InitBackground::sample(const Ray& ray) const
{
    vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    vec3 temp= (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    // 向量转RGB本应该是非法操作
    return rgb3(temp.e[0], temp.e[1], temp.e[2]);
}
