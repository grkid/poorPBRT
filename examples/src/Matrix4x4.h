#pragma once
#include "Eigen/Dense"
#include "vec3.h"
#include "point3.h"
#include "Angle.h"

// 特供变换矩阵。可以与老类型兼容。
// 对于一个渲染器而言，除了某些材质（荧光），对矩阵的需求均为变换矩阵（吗？）
class Matrix4x4
{
private:
	Eigen::Matrix4d mat = Eigen::Matrix4d::Identity();
	bool tained = true; // dirty位，指示矩阵是否需要更新
	// tainted机制对外部透明。
	Eigen::Matrix4d rotMat = Eigen::Matrix4d::Identity();
	Eigen::Matrix4d transMat = Eigen::Matrix4d::Identity();
	Eigen::Matrix4d scaleMat = Eigen::Matrix4d::Identity();

	void update();

public:
	Matrix4x4();

	// 不考虑后续变化，要求一次性输入所有数据
	// 使用的单位全部为弧度

	// Euler X-Y-Z
	void rotate(const Angle& x, const Angle& y, const Angle& z);

	void translate(double x, double y, double z);

	void scale(double x, double y, double z);

	void scale(double ratio);

	// 点需要考虑所有的变换，而向量只需要考虑旋转
	/*friend vec3 operator*(Matrix4x4& mat, const vec3& v);*/
	friend vec3 operator*(std::shared_ptr<Matrix4x4> mat, const vec3& v);
	friend point3 operator*(std::shared_ptr<Matrix4x4> mat, const point3& v);
};

