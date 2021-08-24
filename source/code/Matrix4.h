#pragma once

#include <vector>

class Vec4;
class Vec3;

const class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	void Translate(Vec3 Pos);
	void Scale(float scale);
	
	Vec3 GetPos();
	Vec3 GetLookAt();
	Vec3 GetScale();

	void RotateX(float rot);
	void RotateY(float rot);
	void RotateZ(float rot);

	std::vector<Vec4> m_mat;
private:

};