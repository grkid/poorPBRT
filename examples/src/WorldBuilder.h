#pragma once
#include "Scene.h"
class WorldBuilder
{
public:
	// ǰconst���ܱ��������const���ܱ��Լ�
	virtual void build(Scene& world) const= 0;
};

