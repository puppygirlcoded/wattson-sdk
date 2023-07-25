#pragma once
#include <chrono>
#include "Form/Form.hpp"
#include "Other/Utils.hpp"

class ClickFramework
{
public:
    void CreateInstance();

    Form* AddForm(const std::string& m_sIdentifier, EFormFlags m_eFormFlags = EFormFlags::EFormFlagNone);
    Form* GetForm(const std::string& m_sIdentifier);

    std::string GetActiveForm();

    void SetActiveForm(const std::string& m_sNewIdentifier)
    {
        this->ActiveIdentifier = m_sNewIdentifier;
    }

    void CheckActiveForm(Form* form);

    void ResetActiveForm(Form* form);

    void PollEvents();
private:
    bool m_bHasCreatedInstance = false;
    std::vector<Form> m_arrForms;
    Wattson::Vector2f m_vecInitialPosition;
    std::string ActiveIdentifier;
};

inline auto g_Framework = std::make_unique<ClickFramework>();
