#include <vendor/std.hpp>

#include "Framework.hpp"

void ClickFramework::CreateInstance()
{
    if (this->m_bHasCreatedInstance)
    {
        return;
    }

    this->m_vecInitialPosition = Wattson::Vector2f(50.f, 50.f);

    auto CombatForm = this->AddForm("Combat", EFormFlagOpenCollapsedState);
    
    auto VisualsForm = this->AddForm("Visuals");
    VisualsForm->AddControl("Name ESP", &g_Vars->Visuals.Name);
    VisualsForm->AddControl("Tracer ESP", &g_Vars->Visuals.Snaplines);
    VisualsForm->AddControl("Fullbright", &g_Vars->Visuals.Fullbright);

    auto ClickerForm = this->AddForm("Clicker");

    auto MovementForm = this->AddForm("Movement");

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

void ClickFramework::PollEvents()
{
    g_WattsonRender->Begin();

    for (auto& Form : this->m_arrForms)
    {
        this->CheckActiveForm(&Form);

        // Poll events from each form
        Form.Poll();

        this->ResetActiveForm(&Form);
    }
}
