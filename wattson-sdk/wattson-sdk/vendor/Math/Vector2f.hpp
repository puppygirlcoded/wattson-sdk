#pragma once

struct Vector2f
{
	float x, y;

	Vector2f() 
	{
		x = y = 0.f;
	}

	Vector2f(float scalar)
	{
		x = y = scalar;
	}

	Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2f operator+(const Vector2f& m_vecOther) const
	{
		return Vector2f(x + m_vecOther.x, y + m_vecOther.y);
	}

	Vector2f operator+(const float& m_flOther) const
	{
		return Vector2f(x + m_flOther, y + m_flOther);
	}

	Vector2f operator-(const Vector2f& m_vecOther) const
	{
		return Vector2f(x - m_vecOther.x, y - m_vecOther.y);
	}

	Vector2f operator-(const float& m_flOther) const
	{
		return Vector2f(x - m_flOther, y - m_flOther);
	}

	Vector2f operator*(const Vector2f& m_vecOther) const
	{
		return Vector2f(x * m_vecOther.x, y * m_vecOther.y);
	}

	Vector2f operator*(const float& m_flOther) const
	{
		return Vector2f(x * m_flOther, y * m_flOther);
	}

	Vector2f operator/(const Vector2f& m_vecOther) const
	{
		return Vector2f(x / m_vecOther.x, y / m_vecOther.y);
	}

	Vector2f operator/(const float& m_flOther) const
	{
		return Vector2f(x / m_flOther, y / m_flOther);
	}
};