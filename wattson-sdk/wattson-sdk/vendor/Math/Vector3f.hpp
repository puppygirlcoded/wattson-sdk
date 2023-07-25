#pragma once

struct Vector3f
{
	Vector3f operator + (const Vector3f& rhs) const { return Vector3f(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3f operator + (const float rhs) const { return Vector3f(x + rhs, y + rhs, z + rhs); }
	Vector3f operator - (const Vector3f& rhs) const { return Vector3f(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3f operator - (const float rhs) const { return Vector3f(x - rhs, y - rhs, z - rhs); }
	Vector3f operator * (const Vector3f& rhs) const { return Vector3f(x * rhs.x, y * rhs.y, z * rhs.z); }
	Vector3f operator * (const float& rhs) const { return Vector3f(x * rhs, y * rhs, z * rhs); }
	Vector3f operator / (const float& rhs) const { return Vector3f(x / rhs, y / rhs, z / rhs); }
	Vector3f& operator += (const Vector3f& rhs) { return *this = *this + rhs; }
	Vector3f& operator -= (const Vector3f& rhs) { return *this = *this - rhs; }
	Vector3f& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3f& operator /= (const float& rhs) { return *this = *this / rhs; }
	bool operator!=(Vector3f& rhs) { return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
	bool operator==(Vector3f& rhs) { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }

	Vector3f Invert() const { return Vector3f(-x, -y, -z); }

	inline float& operator[] (int i) { return ((float*)this)[i]; }

	inline float operator[] (int i) const { return ((float*)this)[i]; }

	inline float Length2D() const {
		return sqrt((x * x) + (y * y));
	}

	inline Vector3f Distance(Vector3f other) {
		return other - *this;
	}

	inline float Length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	inline double DistanceSqrt(const Vector3f& other) const {
		return sqrt(pow(x - other.x, 2.0) + pow(y - other.y, 2.0) + pow(z - other.z, 2.0));
	}

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};