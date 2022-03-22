#pragma once
#include "vec3.h"
#include "point3.h"
#include "vec3util.h"
#include <memory>
class Material;
class HitRecord
{
public:
    double t;     //�������ߵĳ���
    point3 p;      //�����յ�����
    vec3 normal; //���е�ķ�����
    std::shared_ptr<Material> mat_ptr; //new
    double u, v;
};

