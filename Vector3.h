#pragma once
#include <DirectXMath.h>

struct Vector3 : public DirectX::XMFLOAT3
{
	Vector3();
	Vector3(float x, float y, float z);

	float Length() const;
	Vector3& Normalize();
	float Dot(const Vector3& v)const;
	Vector3 Cross(const Vector3& v)const;
	DirectX::XMVECTOR ConvertXMVECTOR();

	Vector3 Lerp(const Vector3& a, const Vector3& b, const float time);
	static const Vector3 Zero;
	float Distance(const Vector3& a, const Vector3& b);

	Vector3 operator+() const;
	Vector3 operator-() const;

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const float scalar) const;
	Vector3 operator/(const float scalar) const;

	Vector3 operator+=(const Vector3& v);
	Vector3 operator-=(const Vector3& v);
	Vector3 operator*=(float s);
	Vector3 operator/=(float s);
};
