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
	void SetWorldPosition(Vec3 Pos);
	Vec3 GetWorldPosition();
	void Scale(float scale);
	
	Vec3 GetPos();
	Vec3 GetLookAt();
	Vec3 GetScale();

	Matrix4& RotateX(float rot);
	Matrix4& RotateY(float rot);
	Matrix4& RotateZ(float rot);
	Matrix4& RotateXY(Vec2 rot);
	Matrix4& RotateXZ(Vec2 rot);
	Matrix4& Rotate(Vec3 rot);

	Vec4 m0;
	Vec4 m1;
	Vec4 m2;
	Vec4 m3;

	Matrix4 operator*(const Matrix4& rIn) const
	{
		Matrix4 out = Matrix4();

		if (m0.w == 0.0f && rIn.m0.w == 0.0f &&
			m1.w == 0.0f && rIn.m1.w == 0.0f &&
			m2.w == 0.0f && rIn.m2.w == 0.0f &&
			m3.w == 1.0f && rIn.m3.w == 1.0f)
		{
			out.m0 = rIn.m0 * m0.x + rIn.m1 * m0.y + rIn.m2 * m0.z;
			out.m1 = rIn.m0 * m1.x + rIn.m1 * m1.y + rIn.m2 * m1.z;
			out.m2 = rIn.m0 * m2.x + rIn.m1 * m2.y + rIn.m2 * m2.z;
			out.m3 = rIn.m0 * m3.x + rIn.m1 * m3.y + rIn.m2 * m3.z + rIn.m3;
			out.m0.w = 0.0f;
			out.m1.w = 0.0f;
			out.m2.w = 0.0f;
			out.m3.w = 1.0f;
		}
		else
		{
			const Vec4* pIn = (const Vec4*)&rIn;
			Vec4* pResult = (Vec4*)&out;

			pResult[0] = pIn[0] * m0.x + pIn[1] * m0.y + pIn[2] * m0.z + pIn[3] * m0.w;
			pResult[1] = pIn[0] * m1.x + pIn[1] * m1.y + pIn[2] * m1.z + pIn[3] * m1.w;
			pResult[2] = pIn[0] * m2.x + pIn[1] * m2.y + pIn[2] * m2.z + pIn[3] * m2.w;
			pResult[3] = pIn[0] * m3.x + pIn[1] * m3.y + pIn[2] * m3.z + pIn[3] * m3.w;
		}

		return out;
	}

private:


};

Vec4 operator*(const Matrix4& m, const Vec4& v);
