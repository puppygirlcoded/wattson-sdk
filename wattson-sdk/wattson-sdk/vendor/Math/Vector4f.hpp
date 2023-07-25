#pragma once

struct Vector4f
{
	float x, y, z, w;

	Vector4f()
	{
		x = y = z = w = 0.f;
	}

	Vector4f(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};