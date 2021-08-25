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
	m3 = Vec4(Pos, 0);
}

Matrix4& Matrix4::RotateX(Matrix4& rIn, Matrix4& rOut, float rot)
{
	Matrix4 r = Matrix4();
	r.m0 = Vec4(1, 0, 0, 0);
	r.m1 = Vec4(0, cos(rot), -sin(rot), 0);
	r.m2 = Vec4(0, sin(rot), cos(rot), 0);
	r.m3 = Vec4(0, 0, 0, 1);

	rOut = r * rIn;
	return rOut;
}

Matrix4& Matrix4::RotateY(Matrix4& rIn, Matrix4& rOut, float rot)
{
	Matrix4 r = Matrix4();
	r.m0 = Vec4(cos(rot), 0, sin(rot), 0);
	r.m1 = Vec4(0, 1, 0, 0);
	r.m2 = Vec4(-sin(rot), 0, cos(rot), 0);
	r.m3 = Vec4(0, 0, 0, 1);

	rOut = r * rIn;
	return rOut;
}

Matrix4& Matrix4::RotateZ(Matrix4& rIn, Matrix4& rOut, float rot)
{
	Matrix4 r = Matrix4();
	r.m0 = Vec4(cos(rot), -sin(rot), 0, 0);
	r.m1 = Vec4(sin(rot), cos(rot), 0, 0);
	r.m2 = Vec4(0, 0, 1, 0);
	r.m3 = Vec4(0, 0, 0, 1);

	rOut = r * rIn;
	return rOut;
}

Matrix4& Matrix4::Rotate(Matrix4& rIn, Matrix4& rOut, Vec3 rot)
{
	rOut = RotateX(rIn, rOut, rot.x);
	rOut = RotateY(rIn, rOut, rot.y);
	rOut = RotateZ(rIn, rOut, rot.z);

	return rOut;
}

Vec3 Matrix4::GetRotation()
{
	Vec4 rot = GetRotationMat() * Vec4(1, 1, 1, 0);

	printf("rot: X: %f Y: %f Z: %f\n", rot.x, rot.y, rot.z);

	return Vec3(rot.x, rot.y, rot.z);
}

Matrix4 Matrix4::GetRotationMat()
{
	Vec3 scale = GetScale();
	Matrix4 mat = Matrix4();

	mat.m0 = Vec4(m0.x / scale.x, m0.y / scale.y, m0.z / scale.z, 0);
	mat.m1 = Vec4(m1.x / scale.x, m1.y / scale.y, m1.z / scale.z, 0);
	mat.m2 = Vec4(m2.x / scale.x, m2.y / scale.y, m2.z / scale.z, 0);

	return mat;
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
	printf("rot: X: %f Y: %f Z: %f\n", m2.x, m2.y, m2.z);
	return Vec3(m2.x, m2.y, m2.z);
}

Vec4 operator*(const Matrix4& m, const Vec4& v)
{
	Vec4 out = Vec4(0);

	out.x = m.m0.x * v.x + m.m0.y * v.x + m.m0.z * v.x + m.m0.w * v.x;
	out.y = m.m1.y * v.y + m.m1.y * v.y + m.m1.z * v.y + m.m1.w * v.y;
	out.z = m.m2.z * v.z + m.m2.y * v.z + m.m2.z * v.z + m.m2.w * v.z;
	out.w = m.m3.w * v.w + m.m3.y * v.w + m.m3.z * v.w + m.m3.w * v.w;

	return out;
}
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 out = Matrix4();

	out.m0.x = m1.m0.x * m2.m0.x + m1.m0.y * m2.m0.x + m1.m0.z * m2.m0.x + m1.m0.w * m2.m0.x;
	out.m1.y = m1.m1.y * m2.m1.y + m1.m1.y * m2.m1.y + m1.m1.z * m2.m1.y + m1.m1.w * m2.m1.y;
	out.m2.z = m1.m2.z * m2.m2.z + m1.m2.y * m2.m2.z + m1.m2.z * m2.m2.z + m1.m2.w * m2.m2.z;
	out.m3.w = m1.m3.w * m2.m3.w + m1.m3.y * m2.m3.w + m1.m3.z * m2.m3.w + m1.m3.w * m2.m3.w;

	return out;
}