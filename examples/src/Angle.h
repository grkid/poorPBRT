#pragma once
// 简单的角度和弧度转化封装，省得搞错

enum class AngleType { ANGLE_DEG, ANGLE_RAD };
class Angle
{
private:
	double deg;
	double rad;
public:
	Angle(double v, AngleType type=AngleType::ANGLE_DEG);
	double getDeg() const;
	double getRad() const;
};