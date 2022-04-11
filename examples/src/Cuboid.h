#pragma once
#include "Hittable.h"
#include "Surface.h"
class Cuboid :
    public Hittable
{
private:
    // 记录8个顶点，后续改成其他方式
    // 在某个局部坐标下
    // LR: left right
    // UD: up down
    // FB: front back
    point3 pLUF, pLUB;
    point3 pLDF, pLDB;
    point3 pRUF, pRUB;
    point3 pRDF, pRDB;

    Surface L, R, U, D, F, B;

public:

    Cuboid(std::vector<point3> vec,std::shared_ptr<Material> mp);

    Cuboid(const point3* vec,std::shared_ptr<Material> mp);

    // 顺着坐标轴的立方体
    Cuboid(const point3& centre, double radius,std::shared_ptr<Material> mp);

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

