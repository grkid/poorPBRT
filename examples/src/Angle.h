#pragma once
// �򵥵ĽǶȺͻ���ת����װ��ʡ�ø��

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