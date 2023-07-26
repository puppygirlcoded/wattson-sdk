#include "Form.hpp"

#include "../Framework.hpp"

const float m_flFormHeaderHeight = 35.f;

bool Form::IsHovered()
{
    return ImGui::IsMouseHoveringRect(ImVec2(this->GetPosition().x, this->GetPosition().y),
        ImVec2(this->GetPosition().x + this->GetSize().x, this->GetPosition().y + this->GetSize().y), false);
}

bool Form::CanClick()
{
    return this->IsHovered() && g_Framework->GetActiveForm() == this->GetIdentifier();
}

void Form::RenderControls()
{
    this->PollControlInputs();
}

void Form::PollControlInputs()
{
    this->ResetControls();

    for (auto& control : this->m_dControls)
    {
        if (!control.m_Object.has_value())
        {
            continue;
        }

        switch (control.Type)
        {
        case ControlTypeCheckbox:
        {
            auto object = std::any_cast<Checkbox_t>(control.m_Object);
            object.Update(this);
        }
        break;
        case ControlTypeSliderFloat:
        {
            auto object = std::any_cast<SliderFloat_t>(control.m_Object);
            object.Update(this);
        }
        break;
        case ControlTypeSliderInt:
        {
            auto object = std::any_cast<SliderInt_t>(control.m_Object);
            object.Update(this);
        }
        break;
        }

        this->UpdateControlCount();
    }
}

void Form::Render()
{
    bool m_bIsActive = this->GetIdentifier() == g_Framework->GetActiveForm();

    auto m_aCollapsedAnimation = g_AnimationManager->Get(this->GetIdentifier(), static_cast<float>(this->m_bIsCollapsed));
    g_AnimationManager->Lerp(this->GetIdentifier(), static_cast<float>(this->m_bIsCollapsed), 15.f);

    Wattson::Color m_colBackgroundColor = Wattson::Color(10, 10, 10);
    Wattson::Color m_colFirstOutlineColor = Wattson::Color(0, 0, 0);
    Wattson::Color m_colSecondOutlineColor = Wattson::Color(20, 20, 20);

    Wattson::Vector2f m_vecSize = this->GetSize();
    m_vecSize.y = m_flFormHeaderHeight + ((25.f * this->m_dControls.size()) + 10.f) * m_aCollapsedAnimation.m_flValue;
    this->SetSize({ this->GetSize().x, m_vecSize.y });

    const float m_flOffset = m_flFormHeaderHeight / 2.f - g_WattsonRender->GetTextSize(this->GetIdentifier()).y / 2.f;

    // outline
    g_WattsonRender->AddRectFilled(this->GetPosition() - 1.f, m_vecSize + 2.f, m_colFirstOutlineColor, 3.f);
    g_WattsonRender->AddRectFilled(this->GetPosition(), m_vecSize, m_colSecondOutlineColor, 3.f);

    // main rect
    g_WattsonRender->AddRectFilled(this->GetPosition() + 1.f, m_vecSize - 2.f, m_colBackgroundColor, 3.f);

    // collapse button difuser
    Wattson::Vector2f m_vecCollapseButtonStart = this->GetPosition() + Wattson::Vector2f(m_vecSize.x - m_flFormHeaderHeight, 0.f);
    g_WattsonRender->AddRectFilled(m_vecCollapseButtonStart + Wattson::Vector2f(0.f, m_flFormHeaderHeight / 6.f),
        Wattson::Vector2f(1.f, m_flFormHeaderHeight - ((m_flFormHeaderHeight / 6.f) * 2.f)), m_colSecondOutlineColor);

    // line for bottom difuser
    Wattson::Vector2f m_vecDifuserPosition = Wattson::Vector2f(this->GetPosition().x + (m_flFormHeaderHeight / 6.f),
        this->GetPosition().y + m_flFormHeaderHeight);
    Wattson::Vector2f m_vecDifuserSize = Wattson::Vector2f(this->GetSize().x - ((m_flFormHeaderHeight / 6.f) * 2.f), 1.f);

    g_WattsonRender->AddRectFilled(m_vecDifuserPosition + Wattson::Vector2f((m_vecDifuserSize.x / 2.f) * (1.f - m_aCollapsedAnimation.m_flValue), 0.f),
        Wattson::Vector2f(m_vecDifuserSize.x * m_aCollapsedAnimation.m_flValue, m_vecDifuserSize.y),
        m_colSecondOutlineColor.ModifyAlpha(m_aCollapsedAnimation.m_flValue));

    if (g_WattsonRender->IsHoveringRect(m_vecCollapseButtonStart, { m_flFormHeaderHeight })
        && g_WattsonRender->MouseLeftClick()
        && g_Framework->GetActiveForm() == this->GetIdentifier())
    {
        this->m_bIsCollapsed = !this->m_bIsCollapsed;
    }

    const auto m_flArrowHeight = 6.f;
    const auto m_vecArrowStart = this->GetPosition() + Wattson::Vector2f(m_vecSize.x - (m_flOffset * 1.5f + (m_flArrowHeight * 2.f)),
        m_flFormHeaderHeight / 2.f - m_flArrowHeight / 2.f);
    const auto m_vecArrowMiddle = m_vecArrowStart + Wattson::Vector2f(m_flArrowHeight, m_flArrowHeight);
    const auto m_VecArrowEnd = m_vecArrowMiddle + Wattson::Vector2f(m_flArrowHeight, -m_flArrowHeight);

    g_WattsonRender->RotateVerticies(1.25f + (0.5f * m_aCollapsedAnimation.m_flValue), [&]
    {
        g_WattsonRender->AddLine(m_vecArrowStart, m_vecArrowMiddle, m_colSecondOutlineColor.Lerp(Wattson::Color(97, 140, 209),
            m_aCollapsedAnimation.m_flValue), 2.f);
        g_WattsonRender->AddLine(m_vecArrowMiddle, m_VecArrowEnd, m_colSecondOutlineColor.Lerp(Wattson::Color(97, 140, 209),
            m_aCollapsedAnimation.m_flValue), 2.f);

    }, m_vecCollapseButtonStart + m_flFormHeaderHeight / 2.f);

    // header text
    g_WattsonRender->AddText(this->GetIdentifier(), this->GetPosition() + m_flOffset, Wattson::Color(200, 200, 200).
        Lerp(Wattson::Color(97, 140, 209), m_aCollapsedAnimation.m_flValue));

    g_WattsonRender->PushClipRect(this->GetPosition(), m_vecSize);

    this->RenderControls();

    g_WattsonRender->PopClipRect();
}

void Form::Poll()
{
    if (this->IsHovered() && !g_Framework->GetForm(g_Framework->GetActiveForm())->IsHovered() && ImGui::IsMouseClicked(Mouse1))
    {
        g_Framework->SetActiveForm(this->GetIdentifier());
    }

    if (g_WattsonRender->IsHoveringRect(this->GetPosition(), {this->GetSize().x - m_flFormHeaderHeight, m_flFormHeaderHeight})
        && this->CanClick() && g_WattsonRender->MouseLeftClick())
    {
        this->m_bDragging = true;
        this->m_vecDragPosition = this->GetPosition();
        this->m_vecClickPosition = Wattson::Vector2f(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    }

    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        this->m_bDragging = false;
    }

    if (this->m_bDragging)
    {
        auto m_vecDisplaySize = Wattson::Vector2f(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
        auto m_vecNewPosition = this->m_vecDragPosition + Wattson::Vector2f(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y) - this->m_vecClickPosition;

        m_vecNewPosition.x = std::clamp<float>(m_vecNewPosition.x, 10.f, m_vecDisplaySize.x - this->GetSize().x - 10.f);
        m_vecNewPosition.y = std::clamp<float>(m_vecNewPosition.y, 10.f, m_vecDisplaySize.y - this->GetSize().y - 10.f);

        this->SetPosition(m_vecNewPosition);
    }

    this->Render();
}
