#pragma once
#include "vec3.h"

// ”ÎSpectrum∂‘Ω”
class xyz3:public vec3
{
public:
	xyz3() :vec3() {}
	xyz3(double e0, double e1, double e2) :vec3(e0, e1, e2) {}
};