#pragma once
#include "vec3.h"
#include "point3.h"
#include "rgb3.h"
#include "vec3util.h"

class Ray
{
    point3 A; //���
    vec3 B; //����
    double tm; //ʱ��

public:

    Ray() {}
    Ray(const point3& a, const vec3& b,double t=0.0);
    point3 origin() const;
    vec3 direction() const;
    point3 point_at_parameter(double t) const; //�յ������
    double time() const;    //ʱ�䣬ֻ����Ⱦ�ƶ�����ʱ������
};
