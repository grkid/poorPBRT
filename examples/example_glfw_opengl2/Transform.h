#pragma once
#include "vec3.h"
// ���б任�Ļ��ࡣTODO����������
class Transform
{
public:
	virtual void setTransform(vec3 translate, vec3 rotateDeg, double scale) const = 0;

	// ������Ҫ��̬�ص������������ֻ��Ҫ��ʼ��һ�μ��ɡ�
};

