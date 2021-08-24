#include "Matrix4.h"

#include "Utility/Types.h"
#include "Vulkan.h"

Matrix4::Matrix4()
{
	m_mat.resize(4);
	m_mat[0] = Vec4(1, 0, 0, 0);
	m_mat[1] = Vec4(0, 1, 0, 0);
	m_mat[2] = Vec4(0, 0, 1, 0);
	m_mat[3] = Vec4(0, 0, 0, 1);
}

Matrix4::~Matrix4()
{
	m_mat.clear();
}

void Matrix4::Translate(Vec3 Pos)
{
	m_mat[3] = Vec4(Pos, 0);
}

void Matrix4::RotateX(float rot)
{
	m_mat[0] = Vec4(1, 0, 0, 0);
	m_mat[1] = Vec4(0, glm::cos(rot), -glm::sin(rot), 0);
	m_mat[2] = Vec4(0, glm::sin(rot), glm::cos(rot), 0);
}

void Matrix4::RotateY(float rot)
{
	m_mat[0] = Vec4(glm::cos(rot), 0, glm::sin(rot), 0);
	m_mat[1] = Vec4(0, 1, 0, 0);
	m_mat[2] = Vec4(-glm::sin(rot), 0, glm::cos(rot), 0);
}

void Matrix4::RotateZ(float rot)
{
	m_mat[0] = Vec4(glm::cos(rot), -glm::sin(rot), 0, 0);
	m_mat[1] = Vec4(glm::sin(rot), glm::cos(rot), 0, 0);
	m_mat[2] = Vec4(0, 0, 1, 0);
}

Matrix4 Matrix4::Rotate(Vec3 rot)
{
	RotateX(rot.x);
	RotateY(rot.y);
	RotateZ(rot.z);

	Matrix4 mat = Matrix4();
	mat.m_mat = m_mat;
	return mat;
}

Vec3 Matrix4::GetRotation()
{
	Matrix4 mat = Matrix4();
	mat.m_mat = m_mat;
	Vec4 rot = GetRotationMat() * Vec4(1, 1, 1, 0);

	printf("rot: X: %f Y: %f Z: %f\n", rot.x, rot.y, rot.z);

	return Vec3(rot.x, rot.y, rot.z);
}

Matrix4 Matrix4::GetRotationMat()
{
	Vec3 scale = GetScale();
	Matrix4 mat = Matrix4();

	mat.m_mat[0] = Vec4(m_mat[0].x / scale.x, m_mat[0].y / scale.y, m_mat[0].z / scale.z, 0);
	mat.m_mat[1] = Vec4(m_mat[1].x / scale.x, m_mat[1].y / scale.y, m_mat[1].z / scale.z, 0);
	mat.m_mat[2] = Vec4(m_mat[2].x / scale.x, m_mat[2].y / scale.y, m_mat[2].z / scale.z, 0);

	return mat;
}


void Matrix4::Scale(float scale)
{
	m_mat[0] = Vec4(m_mat[0].x * scale, m_mat[0].y, m_mat[0].z, 0);
	m_mat[1] = Vec4(m_mat[1].x, m_mat[1].y * scale, m_mat[1].z, 0);
	m_mat[2] = Vec4(m_mat[2].x, m_mat[2].y, m_mat[2].z * scale, 0);
}

Vec3 Matrix4::GetPos()
{
	return Vec3(m_mat[3].x, m_mat[3].y, m_mat[3].z);
}

Vec3 Matrix4::GetScale()
{
	Vec3 vec;
	vec.x = m_mat[0].x + m_mat[1].x + m_mat[2].x;
	vec.y = m_mat[0].y + m_mat[1].y + m_mat[2].y;
	vec.z = m_mat[0].z + m_mat[1].z + m_mat[2].z;

	return vec;
}

Vec3 Matrix4::GetLookAt()
{
	return Vec3(m_mat[2].x, m_mat[2].y, m_mat[2].z);
}

Vec4 operator*(const Matrix4& m, const Vec4& v)
{
	Vec4 out = Vec4(0);

	out.x = m.m_mat[0].x * v.x + m.m_mat[0].y * v.x + m.m_mat[0].z * v.x + m.m_mat[0].w * v.x;
	out.y = m.m_mat[1].y * v.y + m.m_mat[1].y * v.y + m.m_mat[1].z * v.y + m.m_mat[1].w * v.y;
	out.z = m.m_mat[2].z * v.z + m.m_mat[2].y * v.z + m.m_mat[2].z * v.z + m.m_mat[2].w * v.z;
	out.w = m.m_mat[3].w * v.w + m.m_mat[3].y * v.w + m.m_mat[3].z * v.w + m.m_mat[3].w * v.w;

	return out;
}