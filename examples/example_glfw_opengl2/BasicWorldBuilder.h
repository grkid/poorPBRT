#pragma once
#include "WorldBuilder.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "Surface.h"

#include "Camera.h"

#include "Texture.h"

#include "Light.h"
// ����һ��ֻ�����������
class BasicWorldBuilder :
    public WorldBuilder
{
public:
    virtual void build(HittableList& world) const;
};

