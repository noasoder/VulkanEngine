#pragma once

class Vec2;
class Vec3;
class Vec4;

const class Vec2 {
public:
	float x = 0.0f, y = 0.0f;

	const Vec2(float X, float Y) {
		x = X;
		y = Y;
	};
	const Vec2(float Both) {
		x = Both;
		y = Both;
	};
	const Vec2() {
		x = 0.0f;
		y = 0.0f;
	};
};

const class Vec3 {
public:
	float x = 0.0f, y = 0.0f, z = 0.0f;

	const Vec3(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	};
	const Vec3(float All) {
		x = All;
		y = All;
		z = All;
	};
	const Vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};
	const Vec3(Vec2 Vec, float Z) {
		x = Vec.x;
		y = Vec.y;
		z = Z;
	};
	const Vec3(float X, Vec2 Vec) {
		x = X;
		y = Vec.x;
		z = Vec.y;
	};
};

const class Vec4 {
public:
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

	const Vec4(float X, float Y, float Z, float W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	};
	const Vec4(float All) {
		x = All;
		y = All;
		z = All;
		w = All;
	};
	const Vec4() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	};
	const Vec4(Vec2 Vec, float Z, float W) {
		x = Vec.x;
		y = Vec.y;
		z = Z;
		w = W;
	};
	const Vec4(float X, float Y, Vec2 Vec) {
		x = X;
		y = Y;
		z = Vec.x;
		w = Vec.y;
	};
	const Vec4(float X, Vec2 Vec, float W) {
		x = X;
		y = Vec.x;
		z = Vec.y;
		w = W;
	};
	const Vec4(Vec3 Vec, float W) {
		x = Vec.x;
		y = Vec.y;
		z = Vec.z;
		w = W;
	};
	const Vec4(float X, Vec3 Vec) {
		x = X;
		y = Vec.x;
		z = Vec.y;
		w = Vec.z;
	};
};

Vec2 operator+(const Vec2& v1, const Vec2& v2);
Vec2 operator-(const Vec2& v1, const Vec2& v2);
Vec2 operator*(const Vec2& v1, const Vec2& v2);
Vec2 operator/(const Vec2& v1, const Vec2& v2);

Vec3 operator+(const Vec3& v1, const Vec3& v2);
Vec3 operator+(const int v1, const Vec3& v2);
Vec3 operator+(const float v1, const Vec3& v2);
Vec3 operator-(const Vec3& v1, const Vec3& v2);
Vec3 operator*(const Vec3& v1, const Vec3& v2);
Vec3 operator/(const Vec3& v1, const Vec3& v2);

Vec4 operator+(const Vec4& v1, const Vec4& v2);
Vec4 operator-(const Vec4& v1, const Vec4& v2);
Vec4 operator*(const Vec4& v1, const Vec4& v2);
Vec4 operator/(const Vec4& v1, const Vec4& v2);