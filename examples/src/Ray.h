#pragma once
#include "vec3.h"
#include "point3.h"
#include "rgb3.h"
#include "vec3util.h"

class Ray
{
    point3 A; //起点
    vec3 B; //方向
    double tm; //时间

public:

    Ray() {}
    Ray(const point3& a, const vec3& b,double t=0.0);
    point3 origin() const;
    vec3 direction() const;
    point3 point_at_parameter(double t) const; //终点的坐标
    double time() const;    //时间，只在渲染移动物体时起作用
};
