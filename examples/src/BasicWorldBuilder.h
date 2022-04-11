#pragma once
#include "WorldBuilder.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#include "Hittable.h"
#include "Scene.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "Surface.h"

#include "Camera.h"

#include "Texture.h"

#include "Emit.h"
// ����һ��ֻ�����������
class BasicWorldBuilder :
    public WorldBuilder
{
public:
    virtual void build(Scene& world) const;
};

