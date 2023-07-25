#include "Slider.hpp"
#include "../../Form/Form.hpp"
#include "../../Framework.hpp"

size_t* m_uBlocking = 0;

template <typename T>
T MapNumber(const T& Input, const T& InputMin, const T& InputMax, const T& OutputMin, const T& OutputMax) {
    return (Input - InputMin) / (InputMax - InputMin) * (OutputMax - OutputMin) + OutputMin;
}

void Slider_t::Update(void* m_pParent)
{
    auto parent = (Form*)m_pParent;

    this->m_vecPosition = parent->GetPosition() + Wattson::Vector2f(0.f, 35.f + (25.f * parent->GetControlCount()));
    m_vecParentSize = parent->GetSize();
    m_bParentIsCollapsed = parent->IsCollapsed();
    m_bIsParentActive = g_Framework->GetActiveForm() == parent->GetIdentifier();
    m_uBlocking = parent->GetBlockingContext();

    this->PollInput();

    this->Draw();
}

void Slider_t::PollInput()
{
    Wattson::Vector2f m_vecRectPosition = this->m_vecPosition + 5.f;
    Wattson::Vector2f m_vecFrameSize = Wattson::Vector2f(m_vecParentSize.x - 10.f, 25.f);

    if (!*m_uBlocking)
    {
        if (g_WattsonRender->IsHoveringRect(m_vecRectPosition, m_vecFrameSize) &&
            g_WattsonRender->MouseLeftClick() && m_bParentIsCollapsed && m_bIsParentActive)
        {
            *m_uBlocking = Hash(this->m_sIdentifier);
        }
    }

    if (*m_uBlocking == Hash(this->m_sIdentifier))
    {
        if (!g_WattsonRender->MouseLeftDown())
        {
            *m_uBlocking = 0;
        }

        float m_flMouseOffset = std::clamp<float>(g_WattsonRender->GetMousePos().x - m_vecRectPosition.x, 0.f, m_vecFrameSize.x);
        *this->m_flValue = std::clamp(MapNumber<float>(m_flMouseOffset, 0, m_vecFrameSize.x, this->m_flMin, this->m_flMax), this->m_flMin, this->m_flMax);
    }
   
}

void Slider_t::Draw()
{
    Wattson::Vector2f m_vecRectPosition = this->m_vecPosition + 5.f;
    Wattson::Vector2f m_vecFrameSize = Wattson::Vector2f(m_vecParentSize.x - 10.f, 25.f);

    std::string m_sLocalIdentifier = this->m_sIdentifier;
    std::string m_sValue = std::vformat("{:.1f}", std::make_format_args(*this->m_flValue));

    auto m_aHoldAnimation = g_AnimationManager->Get(this->m_sIdentifier, false);
    auto m_aInterpAnimation = g_AnimationManager->Get(m_sLocalIdentifier.append("#"), false);

    g_AnimationManager->Lerp(this->m_sIdentifier, static_cast<float>(*m_uBlocking == Hash(this->m_sIdentifier)), 15.f);
    g_AnimationManager->Lerp(m_sLocalIdentifier, *this->m_flValue, 15.f);

    const float m_flSliderWidth = MapNumber<float>(m_aInterpAnimation.m_flValue, this->m_flMin, this->m_flMax, 0.f, m_vecFrameSize.x - 8.f);
    if (m_flSliderWidth > 3.f)
    {
        g_WattsonRender->AddRectFilled(m_vecRectPosition + Wattson::Vector2f(4.f, m_vecFrameSize.y - 3.f), { m_flSliderWidth, 3.f },
            Wattson::Color(180, 180, 180).Lerp(Wattson::Color(97, 140, 209), m_aHoldAnimation.m_flValue), 3.f);
    }

    g_WattsonRender->AddText(this->m_sIdentifier, m_vecRectPosition + Wattson::Vector2f(2.f, 0.f) +
        (m_vecFrameSize.y / 2.f - g_WattsonRender->GetTextSize(this->m_sIdentifier).y / 2.f),
        Wattson::Color(180, 180, 180).Lerp(Wattson::Color(97, 140, 209), m_aHoldAnimation.m_flValue));

    g_WattsonRender->AddText(m_sValue, m_vecRectPosition + Wattson::Vector2f(m_vecFrameSize.x - 6.f - g_WattsonRender->GetTextSize(m_sValue).x, 0.f) +
        (m_vecFrameSize.y / 2.f - g_WattsonRender->GetTextSize(this->m_sIdentifier).y / 2.f),
        Wattson::Color(180, 180, 180).Lerp(Wattson::Color(97, 140, 209), m_aHoldAnimation.m_flValue));
}
