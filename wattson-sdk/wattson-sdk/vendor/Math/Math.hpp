#pragma once
#include <chrono>

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "Vector4f.hpp"
#include "Matrix.hpp"

class Math
{
public:
	Vector4f MultiplyMatrix(const Vector4f& v, const Matrix& m);
	bool WorldToScreen(const Vector3f& m_vecPoint, Vector2f& m_vecScreen);
};

inline auto g_Math = std::make_unique<Math>();