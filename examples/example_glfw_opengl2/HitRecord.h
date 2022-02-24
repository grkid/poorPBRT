#pragma once
#include "vec3.h"
#include <memory>
class Material;
class HitRecord
{
public:
    double t;     //命中射线的长度
    vec3 p;      //命中终点坐标
    vec3 normal; //命中点的法向量
    std::shared_ptr<Material> mat_ptr; //new
};

