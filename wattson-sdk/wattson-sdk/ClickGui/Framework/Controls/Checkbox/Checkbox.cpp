#include "Checkbox.hpp"
#include "../../Form/Form.hpp"
#include "../../Framework.hpp"

void Checkbox_t::Update(void* m_pParent)
{
    auto parent = (Form*)m_pParent;

    this->m_vecPosition = parent->GetPosition() + Wattson::Vector2f(0.f, 35.f + (25.f * parent->GetControlCount()));
    m_vecParentSize = parent->GetSize();
    m_bParentIsCollapsed = parent->IsCollapsed();
    m_bIsParentActive = g_Framework->GetActiveForm() == parent->GetIdentifier();

    this->PollInput();

    this->Draw();
}

void Checkbox_t::PollInput()
{
    Wattson::Vector2f m_vecRectPosition = this->m_vecPosition + 5.f;
    Wattson::Vector2f m_vecFrameSize = Wattson::Vector2f(m_vecParentSize.x - 10.f, 25.f);

    if (g_WattsonRender->IsHoveringRect(m_vecRectPosition, m_vecFrameSize) &&
        g_WattsonRender->MouseLeftClick() && m_bParentIsCollapsed && m_bIsParentActive)
    {
        *this->m_bValue = !*this->m_bValue;
    }
}

void Checkbox_t::Draw()
{
    Wattson::Vector2f m_vecRectPosition = this->m_vecPosition + 5.f;
    Wattson::Vector2f m_vecFrameSize = Wattson::Vector2f(m_vecParentSize.x - 10.f, 25.f);

    auto m_aAnimation = g_AnimationManager->Get(this->m_sIdentifier, static_cast<float>(*this->m_bValue));

    g_AnimationManager->Lerp(this->m_sIdentifier, static_cast<float>(*this->m_bValue), 15.f);

    g_WattsonRender->AddText(this->m_sIdentifier, m_vecRectPosition + Wattson::Vector2f(2.f + (8.f * m_aAnimation.m_flValue), 0.f) +
        (m_vecFrameSize.y / 2.f - g_WattsonRender->GetTextSize(this->m_sIdentifier).y / 2.f),
        Wattson::Color(180, 180, 180).Lerp(Wattson::Color(97, 140, 209), m_aAnimation.m_flValue));
}
