#pragma once
#include "vec3.h"
#include "Matrix4x4.h"

// ���б任�Ļ���,�ܹ�ʵʩ�任�����壨������֮�⣿������Ҫ�̳�����ࡣ
class Transform
{
private:
	// �任�Ƿ����£����������Ƿ�Ӧ�ø��¶��㻺��
	// tainted���ƶ�����͸����
	bool tainted = true;
	void checkInit();

protected:
	std::shared_ptr<Matrix4x4> transformMat=nullptr;

	void transformUpdate();
	virtual void update();

	// �Լ�����һ���任���󣬲����ݸ���Ԫ��
	/*void transformGen();*/

public:
	Transform();
	/*Transform(std::shared_ptr<Matrix4x4> ref);*/
	void setTranslate(double x, double y, double z);
	void setRotate(const Angle& x, const Angle& y, const Angle& z);
	void setScale(double x, double y, double z);
	void setScale(double ratio);
	// ����transformGen��
	/*void set(std::shared_ptr<Matrix4x4> ref);*/

	// ��ȡ�任����ָ�룬����Ϊ�Լ��ı任���󣬲����ݸ���Ԫ��
	/*virtual void transformSet(std::shared_ptr<Matrix4x4> ref);*/
};

/*
* ÿһ���̳���Transform���ࣺ
* 1. ��Ҫʵ��update�������Լ�ά����cache����������Ԫ�ص�update
* 2. ��hit֮ǰ����transformUpdateȷ��ӵ�����»���
* 3. �ڳ�ʼ��ʱ�̳�ʼ�����ֶ�
*/

