#pragma once
#include "vec3.h"
#include <memory>
class Material;
class HitRecord
{
public:
    double t;     //�������ߵĳ���
    vec3 p;      //�����յ�����
    vec3 normal; //���е�ķ�����
    std::shared_ptr<Material> mat_ptr; //new
};

