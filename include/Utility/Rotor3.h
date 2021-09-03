#pragma once

#include "Vulkan.h"
#include "Utility/Types.h"
#include "Matrix3.h"
#include "Utility/Maths.h"

struct Bivector3
{
	float b01 = 0;
	float b02 = 0;
	float b12 = 0;

	Bivector3(float b01, float b02, float b12);
};

Bivector3::Bivector3(float b01, float b02, float b12)
	: b01(b01), b02(b02), b12(b12) {}

// Wedge product
inline Bivector3 Wedge(const Vec3& u, const Vec3& v)
{
	Bivector3 ret(
		u.x * v.y - u.y * v.x, // XY
		u.x * v.z - u.z * v.x, // XZ
		u.y * v.z - u.z * v.y  // YZ
	);
	return ret;
}


struct Rotor3
{
	// scalar part
	float a = 1;
	// bivector part
	float b01 = 0;
	float b02 = 0;
	float b12 = 0;

	// default ctor
	Rotor3() {};
	Rotor3(float a, float b01, float b02, float b12);
	Rotor3(float a, const Bivector3& bv);

	// construct the rotor that rotates one vector to another
	Rotor3(const Vec3& vFrom, const Vec3& vTo);
	// angle+axis, or rather angle+plane
	Rotor3(const Bivector3& bvPlane, float angleRadian);

	// rotate a vector by the rotor
	Vec3 rotate(const Vec3& v) const;

	// multiply
	Rotor3 operator*(const Rotor3& r) const;
	Rotor3 operator*=(const Rotor3& r);
	Rotor3 rotate(const Rotor3& r) const;

	// length utility
	Rotor3 reverse() const; // equivalent to conjugate
	float lengthsqrd() const;
	float length() const;
	void normalize();
	Rotor3 normal() const;

	// convert to matrix
	Matrix3 toMatrix3() const;
	Matrix4 toMatrix4() const;
};

// default ctor
Rotor3::Rotor3(float a, float b01, float b02, float b12)
	: a(a), b01(b01), b02(b02), b12(b12) {}

Rotor3::Rotor3(float a, const Bivector3& bv)
	: a(a), b01(bv.b01), b02(bv.b02), b12(bv.b12) {}

// construct the rotor that rotates one vector to another
// uses the usual trick to get the half angle
Rotor3::Rotor3(const Vec3& vFrom, const Vec3& vTo)
{
	a = 1 + Dot(vTo, vFrom);
	// the left side of the products have b a, not a b, so flip
	Bivector3 minusb = Wedge(vTo, vFrom);
	b01 = minusb.b01;
	b02 = minusb.b02;
	b12 = minusb.b12;
	normalize();
}

// angle+plane, plane must be normalized
Rotor3::Rotor3(const Bivector3& bvPlane, float angleRadian)
{
	float sina = sin(angleRadian / 2.f);
	a = cos(angleRadian / 2.f);
	// the left side of the products have b a, not a b
	b01 = -sina * bvPlane.b01;
	b02 = -sina * bvPlane.b02;
	b12 = -sina * bvPlane.b12;
}

// Rotor3-Rotor3 product
// non-optimized
inline Rotor3 Rotor3::operator*(const Rotor3& q) const
{
	const Rotor3& p = *this;
	Rotor3 r;

	// here we just expanded the geometric product rules



	r.a = p.a * q.a
		- p.b01 * q.b01 - p.b02 * q.b02 - p.b12 * q.b12;

	r.b01 = p.b01 * q.a + p.a * q.b01
		+ p.b12 * q.b02 - p.b02 * q.b12;

	r.b02 = p.b02 * q.a + p.a * q.b02
		- p.b12 * q.b01 + p.b01 * q.b12;

	r.b12 = p.b12 * q.a + p.a * q.b12
		+ p.b02 * q.b01 - p.b01 * q.b02;

	return r;
}

/// R x R*
// non-optimized
Vec3 Rotor3::rotate(const Vec3& x) const
{
	const Rotor3& p = *this;

	// q = P x
	Vec3 q;
	q.x = p.a * x.x + x.y * p.b01 + x.z * p.b02;
	q.y = p.a * x.y - x.x * p.b01 + x.z * p.b12;
	q.z = p.a * x.z - x.x * p.b02 - x.y * p.b12;

	float q012 = x.x * p.b12 - x.y * p.b02 + x.z * p.b01; // trivector

	// r = q P*
	Vec3 r;
	r.x = p.a * q.x + q.y * p.b01 + q.z * p.b02 + q012 * p.b12;
	r.y = p.a * q.y - q.x * p.b01 - q012 * p.b02 + q.z * p.b12;
	r.z = p.a * q.z + q012 * p.b01 - q.x * p.b02 - q.y * p.b12;

	// trivector part of the result is always zero!

	return r;
}

// Rotor3-Rotor3 product
inline Rotor3 Rotor3::operator*=(const Rotor3& r)
{
	(*this) = (*this) * r;
	return *this;
}

// rotate a rotor by another
inline Rotor3 Rotor3::rotate(const Rotor3& r) const
{
	// should unwrap this for efficiency
	return (*this) * r * (*this).reverse();
}


// Equivalent to conjugate
inline Rotor3 Rotor3::reverse() const
{
	return Rotor3(a, -b01, -b02, -b12);
}
// Length Squared
inline float Rotor3::lengthsqrd() const
{
	return sqrt(a) + sqrt(b01) + sqrt(b02) + sqrt(b12);
}
// Length
inline float Rotor3::length() const
{
	return sqrt(lengthsqrd());
}
// Normalize
inline void Rotor3::normalize()
{
	float l = length();
	a /= l; b01 /= l; b02 /= l; b12 /= l;
}
// Normalized rotor
inline Rotor3 Rotor3::normal() const
{
	Rotor3 r = *this;
	r.normalize();
	return r;
}

// convert to matrix
// non-optimized
inline Matrix3 Rotor3::toMatrix3() const
{
	Vec3 v0 = rotate(Vec3(1, 0, 0));
	Vec3 v1 = rotate(Vec3(0, 1, 0));
	Vec3 v2 = rotate(Vec3(0, 0, 1));
	return Matrix3(v0, v1, v2);
}

inline Matrix4 Rotor3::toMatrix4() const
{
	Vec4 v0 = Vec4(rotate(Vec3(1, 0, 0)), 0);
	Vec4 v1 = Vec4(rotate(Vec3(0, 1, 0)), 0);
	Vec4 v2 = Vec4(rotate(Vec3(0, 0, 1)), 0);
	Vec4 v3 = Vec4(0, 0, 0, 1);
	return Matrix4(v0, v1, v2, v3);
}

// geometric product (for reference), produces twice the angle, negative direction
inline Rotor3 Geo(const Vec3& a, const Vec3& b)
{
	return Rotor3(Dot(a, b), Wedge(a, b));
}