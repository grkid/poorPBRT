#pragma once
#include "Scene.h"
class WorldBuilder
{
public:
	// 前const不能变参数，后const不能变自己
	virtual void build(Scene& world) const= 0;
};

