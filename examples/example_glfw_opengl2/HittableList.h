#pragma once
#include "Hittable.h"

// ����ļ̳�
class HittableList : public Hittable
{
public:
    Hittable** list;
    int list_size;

    HittableList() {}
    HittableList(Hittable** l, int n);
    //��������ˣ����м�¼���浽rec
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
};