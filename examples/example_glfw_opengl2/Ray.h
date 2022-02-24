#pragma once
#include "vec3.h"
class Ray
{
    vec3 A; //起点
    vec3 B; //方向
    double tm; //时间

public:

    Ray() {}
    Ray(const vec3& a, const vec3& b,double t=0.0);
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(double t) const; //终点的坐标
    double time() const;
};
