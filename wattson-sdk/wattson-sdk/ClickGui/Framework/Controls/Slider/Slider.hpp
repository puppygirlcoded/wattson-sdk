#pragma once
#include <string>
#include "../../Object/Object.hpp"

struct Slider_t
{
    std::string m_sIdentifier;
    float* m_flValue;
    float m_flMin;
    float m_flMax;

    EControlType Type = ControlTypeSlider;
    Wattson::Vector2f m_vecPosition = 0.f;
    Wattson::Vector2f m_vecParentSize = 0.f;

    bool m_bParentIsCollapsed = false;
    bool m_bIsParentActive = false;

    void PollInput();
    void Draw();
    void Update(void* m_pParent);
};
