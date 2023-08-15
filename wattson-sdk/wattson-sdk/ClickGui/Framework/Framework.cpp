#include <vendor/std.hpp>

#include "Framework.hpp"

void ClickFramework::CreateInstance()
{
    if (this->m_bHasCreatedInstance)
    {
        return;
    }

    this->m_vecInitialPosition = Wattson::Vector2f(50.f, 50.f);

    if (auto CombatForm = this->AddForm("Combat"))
    {
        
    }
    
    if (auto VisualsForm = this->AddForm("Visuals", EFormFlagOpenCollapsedState))
    {
        VisualsForm->AddControl("Name", &g_Vars->Visuals.Name);
        VisualsForm->AddControl("Box", &g_Vars->Visuals.Box);
        VisualsForm->AddControl("Health", &g_Vars->Visuals.Health);
        VisualsForm->AddControl("Tracer", &g_Vars->Visuals.Snaplines);
        if (g_Wattson->g_Utils.m_iMinecraftVersion == 1)
        {
            VisualsForm->AddControl("Glow", &g_Vars->Visuals.Glow);
        }
        VisualsForm->AddControl("Fullbright", &g_Vars->Visuals.Fullbright);
    }
    
    if (auto ClickerForm = this->AddForm("Clicker"))
    {
        ClickerForm->AddControl("Enable", &g_Vars->Clicker.Enabled);
        ClickerForm->AddControl("Minimum CPS", &g_Vars->Clicker.MinimumCPS, 0, 25);
        ClickerForm->AddControl("Maximum CPS", &g_Vars->Clicker.MaximumCPS, 0, 25);
    }

    if (auto MovementForm = this->AddForm("Movement"))
    {
        MovementForm->AddControl("Knockback Modifier", &g_Vars->Movement.KnockbackModifier);
        MovementForm->AddControl("Value", &g_Vars->Movement.KnockbackModifierValue, 0.f, 1.f);
        MovementForm->AddControl("Fast Stop", &g_Vars->Movement.FastStop);
    }

    if (auto HelpersForm = this->AddForm("Helpers"))
    {
        HelpersForm->AddControl("Fast Place", &g_Vars->Helpers.FastPlace);
    }

    this->m_bHasCreatedInstance = true;
}

Form* ClickFramework::AddForm(const std::string& m_sIdentifier, EFormFlags m_eFormFlags)
{
    const bool m_bIsFirstForm = this->m_arrForms.empty();
    Form NewForm = Form(m_sIdentifier, this->m_vecInitialPosition);

    NewForm.SetBlockingContext(0);

    if (m_eFormFlags & EFormFlagOpenCollapsedState)
    {
        NewForm.ToggleCollapsedState();
    }

    this->m_arrForms.push_back(NewForm);

    this->m_vecInitialPosition = this->m_vecInitialPosition + Wattson::Vector2f(300.f, 0.f);

    if (m_bIsFirstForm)
    {
        this->ActiveIdentifier = m_sIdentifier;
    }

    return &this->m_arrForms.back();
}

Form* ClickFramework::GetForm(const std::string& m_sIdentifier)
{
    for (auto& Form : this->m_arrForms)
    {
        if (Form.GetIdentifier() != m_sIdentifier)
        {
            continue;
        }

        return &Form;
    }

    return nullptr;
}

std::string ClickFramework::GetActiveForm()
{
    return this->ActiveIdentifier;
}

void ClickFramework::CheckActiveForm(Form* form)
{
    if (this->GetActiveForm() == form->GetIdentifier())
    {
        g_WattsonRender->SetActiveDrawlist(ImGui::GetForegroundDrawList());
    }
}

void ClickFramework::ResetActiveForm(Form* form)
{
    if (this->GetActiveForm() == form->GetIdentifier())
    {
        g_WattsonRender->SetActiveDrawlist(ImGui::GetBackgroundDrawList());
    }
}

void ClickFramework::Watermark()
{
    int m_iOffset = 0;
    auto RenderItem = [&](const std::string& m_sFirstLabel, const std::string& m_sSecondLabel) -> void
    {
        const auto m_vecFirstTextSize = g_WattsonRender->GetTextSize(m_sFirstLabel);

        g_WattsonRender->AddText(m_sFirstLabel, { 3.f, 2.f + static_cast<float>(m_iOffset) }, Wattson::Color(97, 140, 209));
        g_WattsonRender->AddText(m_sSecondLabel, { 3.f + m_vecFirstTextSize.x, 2.f + static_cast<float>(m_iOffset) }, Wattson::Color(180, 180, 180));

        m_iOffset += m_vecFirstTextSize.y;
    };
    
    RenderItem("Wattson", "Client");
    RenderItem("Version: ", "1.0.0");
    RenderItem("FPS: ", std::to_string(static_cast<int>(ImGui::GetIO().Framerate)));
}

void ClickFramework::PollEvents()
{

    for (auto& Form : this->m_arrForms)
    {
        this->CheckActiveForm(&Form);

        // Poll events from each form
        Form.Poll();

        this->ResetActiveForm(&Form);
    }
}
