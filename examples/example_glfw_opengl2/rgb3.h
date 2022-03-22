#pragma once
#include "vec3.h"
class rgb3 :public vec3
{
	// TODO�������޸�Ϊspectrum
public:
    rgb3() {}
	rgb3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

    inline rgb3& operator+=(const rgb3& v2);
    inline rgb3& operator-=(const rgb3& v2);
    inline rgb3& operator*=(const rgb3& v2);
    /*inline vec3& operator/=(const vec3& v2);*/
    inline rgb3& operator*=(const double t);
    inline rgb3& operator/=(const double t);

    static inline rgb3 fromVec3(const vec3& v) { return rgb3(v.e[0],v.e[1],v.e[2]); }
};