#pragma once

#include <vector>
#include "Utility/Types.h"
class Vec4;
class Vec3;

const class Matrix4
{
public:
	Matrix4();
	Matrix4(Vec4 v0, Vec4 v1, Vec4 v2, Vec4 v3);
	~Matrix4();

	void Translate(Vec3 Pos);
	void Scale(float scale);
	
	Vec3 GetPos();
	Vec3 GetLookAt();
	Vec3 GetScale();
	Vec3 GetRotation();

	Matrix4 GetRotationMat();

	Matrix4& RotateX(Matrix4& rIn, Matrix4& rOut, float rot);
	Matrix4& RotateY(Matrix4& rIn, Matrix4& rOut, float rot);
	Matrix4& RotateZ(Matrix4& rIn, Matrix4& rOut, float rot);
	Matrix4& Rotate(Matrix4& rIn, Matrix4& rOut, Vec3 rot);

	Vec4 m0;
	Vec4 m1;
	Vec4 m2;
	Vec4 m3;

private:


};

Vec4 operator*(const Matrix4& m, const Vec4& v);
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
