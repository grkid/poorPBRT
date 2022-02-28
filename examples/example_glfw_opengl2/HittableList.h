#pragma once
#include "Hittable.h"
#include <vector>

// 诡异的继承
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
    //如果命中了，命中记录保存到rec
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};