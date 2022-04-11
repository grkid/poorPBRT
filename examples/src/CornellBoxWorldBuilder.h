#pragma once
#include "WorldBuilder.h"
class CornellBoxWorldBuilder :
    public WorldBuilder
{
public:
	virtual void build(Scene& world) const;
};

