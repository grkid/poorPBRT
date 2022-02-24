#pragma once
#include "Hittable.h"

// 诡异的继承
class HittableList : public Hittable
{
public:
    Hittable** list;
    int list_size;

    HittableList() {}
    HittableList(Hittable** l, int n);
    //如果命中了，命中记录保存到rec
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
};