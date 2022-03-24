#pragma once
#include "vec3.h"
class xyz3;
class rgb3 :public vec3
{
	// TODO：后续修改为spectrum
public:
    rgb3() {}
	rgb3(double e0, double e1, double e2) :vec3(e0,e1,e2){ }

    /*inline rgb3& operator+=(const rgb3& v2);
    inline rgb3& operator-=(const rgb3& v2);
    inline rgb3& operator*=(const rgb3& v2);
    inline vec3& operator/=(const vec3& v2);
    inline rgb3& operator*=(const double t);
    inline rgb3& operator/=(const double t);*/

    static inline rgb3 fromVec3(const vec3& v) { return rgb3(v.e[0],v.e[1],v.e[2]); }

    xyz3 toXyz3();
};