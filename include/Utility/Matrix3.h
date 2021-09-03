#pragma once

#include "Utility/Types.h"

class Matrix3
{
public:

	Matrix3();
	Matrix3(Vec3 m0, Vec3 m1, Vec3 m2);
	~Matrix3();

	Vec3 m0;
	Vec3 m1;
	Vec3 m2;

	Matrix3 operator=(const Matrix3& m) { return m; };
private:


};

Vec3 operator*(const Matrix3& m, const Vec3& v);