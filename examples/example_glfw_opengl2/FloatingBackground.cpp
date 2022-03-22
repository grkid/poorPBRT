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

rgb3 FloatingBackground::sample(const Ray& ray) const
{
    // TODO�������������ƺ�ֻ��ͨ������ʵ�֡�
    return rgb3(0, 0, 0);
}
