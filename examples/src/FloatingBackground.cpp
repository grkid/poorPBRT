#include "FloatingBackground.h"
#include "COnstTexture.h"
FloatingBackground::FloatingBackground(const rgb3& color)
{
    baseColor = std::make_shared<ConstTexture>(color);
}

FloatingBackground::FloatingBackground(std::shared_ptr<Texture> color)
{
    baseColor = color;
}

SampledSpectrum FloatingBackground::sample(const Ray& ray) const
{
    // TODO：悬浮背景。似乎只能通过后处理实现。
    return SampledSpectrum(0.0);
}
