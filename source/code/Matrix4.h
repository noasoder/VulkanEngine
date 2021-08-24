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
	Matrix4 Rotate(Vec3 rot);
	
	Vec3 GetPos();
	Vec3 GetLookAt();
	Vec3 GetScale();
	Vec3 GetRotation();

	Matrix4 GetRotationMat();

	void RotateX(float rot);
	void RotateY(float rot);
	void RotateZ(float rot);


	std::vector<Vec4> m_mat;
private:


};

Vec4 operator*(const Matrix4& m, const Vec4& v);
