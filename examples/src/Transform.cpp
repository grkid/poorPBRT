#include "Transform.h"

// Ϊ�Լ�����һ���任����
// ������Σ�ֻҪΪĳ���������ñ任����������Ҫ��֤mat��Ϊ�ա�
// ���״�ʩ��
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
	// ���Գ�ʼ��
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

// �������ڱ����Լ��ĸ���cacheΪ����
void Transform::transformUpdate()
{
	if (tainted == true)
	{
		tainted = false;
		update();
	}
}

// �����Լ��ĸ���cache
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
