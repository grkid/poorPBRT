#pragma once
#include "Hittable.h"
class Sphere : public Hittable
{
public:
    vec3 center;
    float radius;
    Material* mat_ptr; /* NEW */
    Sphere();
    Sphere(vec3 cen, float r, Material* m); //new
    //如果命中了，命中记录保存到rec
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
};
