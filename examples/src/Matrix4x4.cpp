#include "Matrix4x4.h"

void Matrix4x4::update()
{
	if (tained) {
		tained = false;
		// T S R
		mat = transMat * scaleMat * rotMat;
	}
}

Matrix4x4::Matrix4x4() {
	// empty
}

void Matrix4x4::rotate(const Angle& x, const Angle& y, const Angle& z)
{
	tained = true;
	Eigen::Matrix3d block; /*= rotMat.block<3,3>(0, 0);*/
	auto rotX = Eigen::AngleAxisd(x.getRad(), Eigen::Vector3d::UnitX());
	auto rotY = Eigen::AngleAxisd(y.getRad(), Eigen::Vector3d::UnitY());
	auto rotZ = Eigen::AngleAxisd(z.getRad(), Eigen::Vector3d::UnitZ());
	block = rotZ * rotY * rotX;
	rotMat.block<3, 3>(0, 0) = block;
}

void Matrix4x4::translate(double x, double y, double z)
{
	tained = true;
	transMat(0, 3) = x;
	transMat(1, 3) = y;
	transMat(2, 3) = z;
}

void Matrix4x4::scale(double x, double y, double z)
{
	tained = true;
	scaleMat(0, 0) = x;
	scaleMat(1, 1) = y;
	scaleMat(2, 2) = z;
}

void Matrix4x4::scale(double ratio)
{
	tained = true;
	scaleMat(0, 0) = scaleMat(1, 1) = scaleMat(2, 2) = ratio;
}

//vec3 operator*(Matrix4x4& mat, const vec3& v)
//{
//	mat.update();
//	Eigen::Vector4d vec = Eigen::Vector4d(v[0], v[1], v[2], 1.0);
//	Eigen::Vector4d result = mat.mat * vec;
//	return vec3(result[0] / result[3], result[1] / result[3], result[2] / result[3]);
//}

// Matrix4x4类在许多集合中共享
vec3 operator*(std::shared_ptr<Matrix4x4> mat, const vec3& v)
{
	mat->update();
	Eigen::Vector3d vec = Eigen::Vector3d(v[0], v[1], v[2]);
	Eigen::Vector3d result = mat->mat.block<3,3>(0,0) * vec;
	return vec3(result[0], result[1], result[2]);
}

point3 operator*(std::shared_ptr<Matrix4x4> mat, const point3& v)
{
	mat->update();
	Eigen::Vector4d vec = Eigen::Vector4d(v[0], v[1], v[2], 1.0);
	Eigen::Vector4d result = mat->mat * vec;
	return point3(result[0]/result[3], result[1] / result[3], result[2] / result[3]);
}
