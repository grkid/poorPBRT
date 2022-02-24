#pragma once
#include "Ray.h"
#include "HitRecord.h"

class Hittable
{
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};