#pragma once
#include "HittableList.h"
class WorldBuilder
{
public:
	// ǰconst���ܱ��������const���ܱ��Լ�
	virtual void build(HittableList& world) const= 0;
};

