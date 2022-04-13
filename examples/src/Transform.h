#pragma once
#include "vec3.h"
#include "Matrix4x4.h"

// 所有变换的基类,能够实施变换的物体（除了球之外？）都需要继承这个类。
class Transform
{
private:
	// 变换是否最新，用来检验是否应该更新顶点缓存
	// tainted机制对子类透明。
	bool tainted = true;
	void checkInit();

protected:
	std::shared_ptr<Matrix4x4> transformMat=nullptr;

	void transformUpdate();
	virtual void update();

	// 自己生成一个变换矩阵，并传递给子元素
	/*void transformGen();*/

public:
	Transform();
	/*Transform(std::shared_ptr<Matrix4x4> ref);*/
	void setTranslate(double x, double y, double z);
	void setRotate(const Angle& x, const Angle& y, const Angle& z);
	void setScale(double x, double y, double z);
	void setScale(double ratio);
	// 放在transformGen中
	/*void set(std::shared_ptr<Matrix4x4> ref);*/

	// 获取变换矩阵指针，设置为自己的变换矩阵，并传递给子元素
	/*virtual void transformSet(std::shared_ptr<Matrix4x4> ref);*/
};

/*
* 每一个继承了Transform的类：
* 1. 需要实现update，更新自己维护的cache，并调用子元素的update
* 2. 在hit之前调用transformUpdate确保拥有最新缓存
* 3. 在初始化时刻初始矩阵字段
*/

