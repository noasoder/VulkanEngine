
#include "Utility/Types.h"

Vec2 operator+(const Vec2& v1, const Vec2& v2) {
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}
Vec2 operator-(const Vec2& v1, const Vec2& v2) {
	return Vec2(v1.x - v2.x, v1.y - v2.y);
}
Vec2 operator*(const Vec2& v1, const Vec2& v2) {
	return Vec2(v1.x * v2.x, v1.y * v2.y);
}
Vec2 operator/(const Vec2& v1, const Vec2& v2) {
	return Vec2(v1.x / v2.x, v1.y / v2.y);
}

Vec3 operator+(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Vec3 operator-(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
Vec3 operator*(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
Vec3 operator/(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vec4 operator+(const Vec4& v1, const Vec4& v2) {
	return Vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}
Vec4 operator-(const Vec4& v1, const Vec4& v2) {
	return Vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}
Vec4 operator*(const Vec4& v1, const Vec4& v2) {
	return Vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}
Vec4 operator/(const Vec4& v1, const Vec4& v2) {
	return Vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}