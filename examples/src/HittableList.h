#pragma once
#include "Hittable.h"
#include <vector>

// ����ļ̳�
class HittableList : public Hittable
{
    /*Hittable** list;*/
    std::vector<std::shared_ptr<Hittable>> list;
    //int list_size;

public:

    HittableList();
    //HittableList(/*Hittable** l, int n*/);
    HittableList(std::vector<std::shared_ptr<Hittable>> vec);
    void add(std::shared_ptr<Hittable> obj);
    //��������ˣ����м�¼���浽rec
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

    void clear();
};