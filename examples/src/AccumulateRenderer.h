#pragma once
#include "Renderer.h"
// 有点问题。
class AccumulateRenderer :
    public Renderer
{
public:
    AccumulateRenderer();
    AccumulateRenderer(int x, int y, int samples, int depth, int tn, std::shared_ptr<Camera> camera, std::shared_ptr<Background> bg = nullptr);
    virtual void singleThreadRayTracing(int k);
};

