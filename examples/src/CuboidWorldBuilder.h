#pragma once
#include "WorldBuilder.h"
class CuboidWorldBuilder :
    public WorldBuilder
{
public:
    virtual void build(Scene& world) const;
};

