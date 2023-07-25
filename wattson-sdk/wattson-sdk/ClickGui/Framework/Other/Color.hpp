#pragma once
#include <cmath>

namespace Wattson
{
    class Color
    {
    public:
        int r, g, b, a;

        Color()
        {
            r = g = b = a = 255;
        }

        Color(int _r, int _g, int _b, int _a = 255)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

        Color(int scalar)
        {
            r = g = b = a = scalar;
        }

        Color ModifyAlpha(int m_iAlpha)
        {
            return Color(r, g, b, static_cast<int>(a * static_cast<float>(m_iAlpha / 255)));
        }

        Color ModifyAlpha(float m_flAlpha)
        {
            return Color(r, g, b, static_cast<int>(a * m_flAlpha));
        }

        Color OverrideAlpha(int m_iAlpha)
        {
            return Color(r, g, b, m_iAlpha);
        }

        Color Lerp(Color m_colOther, float m_flAdditive)
        {
            // have to divide them for a more accurate lerp

            float red = std::lerp(r / 255.f, m_colOther.r / 255.f, m_flAdditive);
            float green = std::lerp(g / 255.f, m_colOther.g / 255.f, m_flAdditive);
            float blue = std::lerp(b / 255.f, m_colOther.b / 255.f, m_flAdditive);
            float alpha = std::lerp(a / 255.f, m_colOther.a / 255.f, m_flAdditive);

            return Color(red * 255, green * 255, blue * 255, alpha * 255);
        }
    };
}
