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

	Vec2 operator+(const Vec2& v2) const { return Vec2(x + v2.x, y + v2.y); }
	Vec2 operator+(const float& v2) const { return Vec2(x + v2, y + v2); }
	Vec2 operator-(const Vec2& v2) const { return Vec2(x - v2.x, y - v2.y); }
	Vec2 operator*(const Vec2& v2) const { return Vec2(x * v2.x, y * v2.y); }
	Vec2 operator*(const float& v2) const { return Vec2(x * v2, y * v2); }
	Vec2 operator/(const Vec2& v2) const { return Vec2(x / v2.x, y / v2.y); }
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
	Vec3 operator+(const Vec3& v2) const { return Vec3(x + v2.x, y + v2.y, z + v2.z); }
	Vec3 operator+(const float& v2) const { return Vec3(x + v2, y + v2, z + v2); }
	Vec3 operator+(const int& v2) const { return Vec3(x + v2, y + v2, z + v2); }
	Vec3 operator-(const Vec3& v2) const { return Vec3(x - v2.x, y - v2.y, z - v2.z); }
	Vec3 operator*(const Vec3& v2) const { return Vec3(x * v2.x, y * v2.y, z * v2.z); }
	Vec3 operator*=(const Vec3& v2) const { return Vec3(x * v2.x, y * v2.y, z * v2.z); }
	Vec3 operator/(const Vec3& v2) const { return Vec3(x / v2.x, y / v2.y, z / v2.z); }
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

	Vec4 operator+(const Vec4& v2) const { return Vec4(x + v2.x, y + v2.y, z + v2.z, w + v2.w); }
	Vec4 operator-(const Vec4& v2) const { return Vec4(x - v2.x, y - v2.y, z - v2.z, w - v2.w); }
	Vec4 operator*(const float& in) const { return Vec4(x * in, y * in, z * in, w * in); }
	Vec4 operator*(const Vec4& v1) const { return Vec4(x * v1.x, y * v1.y, z * v1.z, w * v1.w); }
	Vec4 operator/(const Vec4& v2) const { return Vec4(x / v2.x, y / v2.y, z / v2.z, w / v2.w); }
};
