#pragma once
#include "vec3.h"

class point3 :public vec3
{
	// ֻ�������֣���vec3û������
public:
    point3() {}
	point3(double e0, double e1, double e2) :vec3(e0,e1,e2){  }

    /*inline point3& operator+=(const vec3& v2);
    inline point3& operator-=(const vec3& v2);*/
    /*inline point3& operator*=(const vec3& v2);
    inline point3& operator/=(const vec3& v2);*/
    /*inline vec3& operator*=(const double t);
    inline vec3& operator/=(const double t);*/
};