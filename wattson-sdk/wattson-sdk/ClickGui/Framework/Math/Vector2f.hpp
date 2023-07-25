#pragma once
#include <imgui.h>

namespace Wattson
{
    class Vector2f
    {
    public:
        float x, y;

        Vector2f()
        {
            x = y = 0.f;
        }

        Vector2f(float _x, float _y)
        {
            x = _x;
            y = _y;
        }

        Vector2f(float scalar)
        {
            x = y = scalar;
        }

        Vector2f operator+(const Vector2f& other) const
        {
            return Vector2f(this->x + other.x, this->y + other.y);
        }

        Vector2f operator-(const Vector2f& other) const
        {
            return Vector2f(this->x - other.x, this->y - other.y);
        }

        Vector2f operator+(const float& other) const
        {
            return Vector2f(this->x + other, this->y + other);
        }

        Vector2f operator-(const float& other) const
        {
            return Vector2f(this->x - other, this->y - other);
        }

        Vector2f operator*(const Vector2f& other) const
        {
            return Vector2f(this->x * other.x, this->y * other.y);
        }

        Vector2f operator/(const Vector2f& other) const
        {
            return Vector2f(this->x / other.x, this->y / other.y);
        }

        Vector2f operator*(const float& other) const
        {
            return Vector2f(this->x * other, this->y * other);
        }

        Vector2f operator/(const float& other) const
        {
            return Vector2f(this->x / other, this->y / other);
        }

        ImVec2 ConvertToImVec2() const
        {
            return ImVec2(x, y);
        }
    };
}
