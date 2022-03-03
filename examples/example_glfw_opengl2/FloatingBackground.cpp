#include "FloatingBackground.h"
#include "COnstTexture.h"
FloatingBackground::FloatingBackground(const vec3& color)
{
    baseColor = std::make_shared<ConstTexture>(color);
}

FloatingBackground::FloatingBackground(std::shared_ptr<Texture> color)
{
    baseColor = color;
}

vec3 FloatingBackground::sample(const Ray& ray) const
{
    // TODO�������������ƺ�ֻ��ͨ������ʵ�֡�
    return vec3(0, 0, 0);
}
