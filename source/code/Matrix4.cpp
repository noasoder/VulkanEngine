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

Vec3 Matrix4::GetRotation()
{
	Vec3 vec;

	vec.x = m_mat[0].x
	return vec;
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
	return Vec3(1);
}

Vec3 Matrix4::GetLookAt()
{
	return Vec3(m_mat[2].x, m_mat[2].y, m_mat[2].z);
}