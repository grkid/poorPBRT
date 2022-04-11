#pragma once
#include "vec3.h"
// 所有变换的基类。TODO：引入矩阵库
class Transform
{
public:
	virtual void setTransform(vec3 translate, vec3 rotateDeg, double scale) const = 0;

	// 并不需要动态地调整场景，因此只需要初始化一次即可。
};

