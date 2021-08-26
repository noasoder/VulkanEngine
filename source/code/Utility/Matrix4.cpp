#include "Matrix4.h"

#include "Utility/Types.h"
#include "Vulkan.h"

Matrix4::Matrix4()
{
	m0 = Vec4(1, 0, 0, 0);
	m1 = Vec4(0, 1, 0, 0);
	m2 = Vec4(0, 0, 1, 0);
	m3 = Vec4(0, 0, 0, 1);
}
Matrix4::Matrix4(Vec4 v0, Vec4 v1, Vec4 v2, Vec4 v3)
{
	m0 = v0;
	m1 = v1;
	m2 = v2;
	m3 = v3;
}

Matrix4::~Matrix4()
{

}

void Matrix4::Translate(Vec3 Pos)
{
	//m3 = Vec4(Pos, 1);

	//Vec3 result;

	m3.x = - Pos.x * m0.x + Pos.y * m1.x + Pos.z * m2.x + 1 * m3.x;
	m3.y = - Pos.x * m0.y + Pos.y * m1.y + Pos.z * m2.y + 1 * m3.y;
	m3.z = - Pos.x * m0.z + Pos.y * m1.z + Pos.z * m2.z + 1 * m3.z;
	m3.w = 1;
}

void Matrix4::SetWorldPosition(Vec3 Pos)
{
	m3 = Vec4(Pos, 1);
}

Vec3 Matrix4::GetWorldPosition()
{
	Vec3 result;
	Vec4 vec = Vec4(0, 0, 0, 1);

	result.x = vec.x * m0.x + vec.y * m1.x + vec.z * m2.x + vec.w * m3.x;
	result.y = vec.x * m0.y + vec.y * m1.y + vec.z * m2.y + vec.w * m3.y;
	result.z = vec.x * m0.z + vec.y * m1.z + vec.z * m2.z + vec.w * m3.z;


	return Vec3(result);
}

Matrix4& Matrix4::RotateX(float rot)
{
	Matrix4 r = Matrix4();
	r.m0 = Vec4(1, 0, 0, 0);
	r.m1 = Vec4(0, cos(rot), -sin(rot), 0);
	r.m2 = Vec4(0, sin(rot), cos(rot), 0);
	r.m3 = Vec4(0, 0, 0, 1);

	*this = r * *this;
	return *this;
}

Matrix4& Matrix4::RotateY(float rot)
{
	Matrix4* pIn;
	Matrix4 r = Matrix4();
	r.m0 = Vec4(cos(rot), -sin(rot), 0, 0);
	r.m1 = Vec4(sin(rot), cos(rot), 0, 0);
	r.m2 = Vec4(0, 0, 1, 0);
	r.m3 = Vec4(0, 0, 0, 1);

	*this = r * *this;
	return *this;
}

Matrix4& Matrix4::RotateZ(float rot)
{
	Matrix4 r = Matrix4();
	r.m0 = Vec4(cos(rot), 0, sin(rot), 0);
	r.m1 = Vec4(0, 1, 0, 0);
	r.m2 = Vec4(-sin(rot), 0, cos(rot), 0);
	r.m3 = Vec4(0, 0, 0, 1);

	*this = r * *this;
	return *this;
}

Matrix4& Matrix4::Rotate(Vec3 rot)
{
	//RAU LBD
	RotateX(rot.x);
	RotateY(rot.y);
	RotateZ(rot.z);

	return *this;
}

Matrix4& Matrix4::RotateXY(Vec2 rot)
{
	RotateX(rot.x);
	RotateY(rot.y);

	return *this;
}
Matrix4& Matrix4::RotateXZ(Vec2 rot)
{
	RotateX(rot.x);
	RotateZ(rot.y);

	return *this;
}

void Matrix4::Scale(float scale)
{
	m0 = Vec4(m0.x * scale, m0.y, m0.z, 0);
	m1 = Vec4(m1.x, m1.y * scale, m1.z, 0);
	m2 = Vec4(m2.x, m2.y, m2.z * scale, 0);
}

Vec3 Matrix4::GetPos()
{
	return Vec3(m3.x, m3.y, m3.z);
}

Vec3 Matrix4::GetScale()
{
	Vec3 vec;
	vec.x = m0.x + m1.x + m2.x;
	vec.y = m0.y + m1.y + m2.y;
	vec.z = m0.z + m1.z + m2.z;

	return vec;
}

Vec3 Matrix4::GetLookAt()
{
	//printf("rot: X: %f Y: %f Z: %f\n", m2.x, m2.y, m2.z);
	return Vec3(m1.x, m1.y, m1.z);
}

Vec4 operator*(const Matrix4& m, const Vec4& v)
{
	Vec4 out = Vec4(0);

	out.x = m.m0.x * v.x + m.m0.y * v.x + m.m0.z * v.x + m.m0.w * v.x;
	out.y = m.m1.x * v.y + m.m1.y * v.y + m.m1.z * v.y + m.m1.w * v.y;
	out.z = m.m2.x * v.z + m.m2.y * v.z + m.m2.z * v.z + m.m2.w * v.z;
	out.w = m.m3.x * v.w + m.m3.y * v.w + m.m3.z * v.w + m.m3.w * v.w;

	return out;
}
