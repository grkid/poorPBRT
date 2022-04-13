#pragma once
#include "Hittable.h"
#include <vector>

class Scene : public Hittable
{
    /*Hittable** list;*/
    std::vector<std::shared_ptr<Hittable>> list;
    //int list_size;

public:

    Scene();
    //HittableList(/*Hittable** l, int n*/);
    Scene(std::vector<std::shared_ptr<Hittable>> vec);
    void add(std::shared_ptr<Hittable> obj);
    //如果命中了，命中记录保存到rec
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec);

    void clear();
};