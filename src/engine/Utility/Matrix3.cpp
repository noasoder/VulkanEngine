#include "Utility/Matrix3.h"

#include "Utility/Types.h"

Matrix3::Matrix3()
{
	m0 = Vec3(1, 0, 0);
	m1 = Vec3(0, 1, 0);
	m2 = Vec3(0, 0, 1);
}

Matrix3::Matrix3(Vec3 v0, Vec3 v1, Vec3 v2)
{
	m0 = v0;
	m1 = v1;
	m2 = v2;
}

Matrix3::~Matrix3()
{

}

Vec3 operator*(const Matrix3& m, const Vec3& v)
{
	Vec3 out = Vec3(0);

	out.x = m.m0.x * v.x + m.m0.y * v.x + m.m0.z * v.x;
	out.y = m.m1.y * v.y + m.m1.y * v.y + m.m1.z * v.y;
	out.z = m.m2.z * v.z + m.m2.y * v.z + m.m2.z * v.z;

	return out;
}