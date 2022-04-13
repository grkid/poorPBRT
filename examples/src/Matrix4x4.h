#pragma once
#include "Eigen/Dense"
#include "vec3.h"
#include "point3.h"
#include "Angle.h"

// �ع��任���󡣿����������ͼ��ݡ�
// ����һ����Ⱦ�����ԣ�����ĳЩ���ʣ�ӫ�⣩���Ծ���������Ϊ�任�����𣿣�
class Matrix4x4
{
private:
	Eigen::Matrix4d mat = Eigen::Matrix4d::Identity();
	bool tained = true; // dirtyλ��ָʾ�����Ƿ���Ҫ����
	// tainted���ƶ��ⲿ͸����
	Eigen::Matrix4d rotMat = Eigen::Matrix4d::Identity();
	Eigen::Matrix4d transMat = Eigen::Matrix4d::Identity();
	Eigen::Matrix4d scaleMat = Eigen::Matrix4d::Identity();

	void update();

public:
	Matrix4x4();

	// �����Ǻ����仯��Ҫ��һ����������������
	// ʹ�õĵ�λȫ��Ϊ����

	// Euler X-Y-Z
	void rotate(const Angle& x, const Angle& y, const Angle& z);

	void translate(double x, double y, double z);

	void scale(double x, double y, double z);

	void scale(double ratio);

	// ����Ҫ�������еı任��������ֻ��Ҫ������ת
	/*friend vec3 operator*(Matrix4x4& mat, const vec3& v);*/
	friend vec3 operator*(std::shared_ptr<Matrix4x4> mat, const vec3& v);
	friend point3 operator*(std::shared_ptr<Matrix4x4> mat, const point3& v);
};

