#pragma once
#include "Hittable.h"
#include "Surface.h"
class Cuboid :
    public Hittable,public Transform
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

    Cuboid(std::vector<point3> vec,std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat=std::make_shared<Matrix4x4>());

    Cuboid(const point3* vec,std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat = std::make_shared<Matrix4x4>());

    // 顺着坐标轴的立方体
    Cuboid(const point3& centre, double radius,std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat = std::make_shared<Matrix4x4>());

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec);

    // Transform
    virtual void update();
   /* virtual void transformSet(std::shared_ptr<Matrix4x4> ref);*/
};

