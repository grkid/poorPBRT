#pragma once
#include "HittableList.h"
class WorldBuilder
{
public:
	// 前const不能变参数，后const不能变自己
	virtual void build(HittableList& world) const= 0;
};

