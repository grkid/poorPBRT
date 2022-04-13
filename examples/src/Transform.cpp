#include "Transform.h"

// 为自己创建一个变换矩阵。
// 无论如何，只要为某个物体设置变换参数，就需要保证mat不为空。
// 兜底措施。
void Transform::checkInit()
{
	if (transformMat == nullptr) {
		tainted = true;
		transformMat = std::make_shared<Matrix4x4>();
	}
}

Transform::Transform()
{
	// empty
	// 惰性初始化
}

//Transform::Transform(std::shared_ptr<Matrix4x4> ref)
//{
//	if(ref!=nullptr)
//		mat = ref;
//	else
//		mat= std::make_shared<Matrix4x4>();
//}

void Transform::setTranslate(double x, double y, double z)
{
	checkInit();
	tainted = true;
	transformMat->translate(x, y, z);
}

void Transform::setRotate(const Angle& x, const Angle& y, const Angle& z)
{
	checkInit();
	tainted = true;
	transformMat->rotate(x, y, z);
}

void Transform::setScale(double x, double y, double z)
{
	checkInit();
	tainted = true;
	transformMat->scale(x, y, z);
}

void Transform::setScale(double ratio)
{
	checkInit();
	tainted = true;
	transformMat->scale(ratio);
}

// 调用用于保持自己的各项cache为最新
void Transform::transformUpdate()
{
	if (tainted == true)
	{
		tainted = false;
		update();
	}
}

// 更新自己的各项cache
void Transform::update()
{
	// empty
}

//void Transform::transformGen()
//{
//	checkInit();
//	transformSet(mat);
//}
//
//void Transform::transformSet(std::shared_ptr<Matrix4x4> ref)
//{
//	tainted = true;
//	mat = ref;
//}
