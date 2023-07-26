#pragma once
#include "../Object/Object.hpp"

#include "../Controls/Checkbox/Checkbox.hpp"
#include "../Controls/Slider/Slider.hpp"

struct ControlObject_t
{
    ControlObject_t(const EControlType m_eType, std::any&& m_aObject) : Type(m_eType), m_Object(std::move(m_aObject)) {}

    EControlType Type = ControlTypeNone;
    std::any m_Object = {};
};

class Form
{
public:

    Form(const std::string& _Identifier)
    {
        this->m_sIdentifier = _Identifier;
        this->SetPosition({ 50.f, 50.f });
        this->SetSize({ 250.f, 35.f });
    }

    Form(const std::string& _Identifier, const Wattson::Vector2f& m_vecIntialPosition)
    {
        this->m_sIdentifier = _Identifier;
        this->SetPosition(m_vecIntialPosition);
        this->SetSize({ 250.f, 35.f });
    }

    std::string GetIdentifier()
    {
        return this->m_sIdentifier;
    }

    Wattson::Vector2f GetPosition()
    {
        return this->m_vecPosition;
    }

    void SetPosition(const Wattson::Vector2f& m_vecNewPosition)
    {
        this->m_vecPosition = m_vecNewPosition;
    }

    Wattson::Vector2f GetSize()
    {
        return this->m_vecSize;
    }

    void SetSize(const Wattson::Vector2f& m_vecNewSize)
    {
        this->m_vecSize = m_vecNewSize;
    }

    void ToggleCollapsedState()
    {
        this->m_bIsCollapsed = !this->m_bIsCollapsed;
    }

    bool IsCollapsed()
    {
        return this->m_bIsCollapsed;
    }

    bool IsHovered();

    bool CanClick();

    void RenderControls();

    void PollControlInputs();

    int GetControlCount()
    {
        return this->m_iControlRenderCount;
    }

    void UpdateControlCount()
    {
        this->m_iControlRenderCount++;
    }

    void ResetControls() {
        this->m_iControlRenderCount = 0;
    }

    size_t* GetBlockingContext()
    {
        return &this->m_uBlocking;
    }

    void SetBlockingContext(size_t m_uBlocking)
    {
        this->m_uBlocking = m_uBlocking;
    }

    void Render();

    void Poll();

    void AddControl(const std::string& m_sIdentifier, bool* m_bValue)
    {
        this->m_dControls.emplace_back(ControlTypeCheckbox, std::make_any<Checkbox_t>(m_sIdentifier, m_bValue));
    }

    void AddControl(const std::string& m_sIdentifier, float* m_flValue, float m_flMin, float m_flMax)
    {
        this->m_dControls.emplace_back(ControlTypeSliderFloat, std::make_any<SliderFloat_t>(m_sIdentifier, m_flValue, m_flMin, m_flMax));
    }

    void AddControl(const std::string& m_sIdentifier, int* m_iValue, int m_iMin, int m_iMax)
    {
        this->m_dControls.emplace_back(ControlTypeSliderInt, std::make_any<SliderInt_t>(m_sIdentifier, m_iValue, m_iMin, m_iMax));
    }


private:
    std::string m_sIdentifier;
    EFormFlags m_eFlags;

    Wattson::Vector2f m_vecPosition;
    Wattson::Vector2f m_vecSize;

    bool m_bIsCollapsed = false;
    std::deque<ControlObject_t> m_dControls;
    int m_iControlRenderCount = 0;
    size_t m_uBlocking = 0;

    bool m_bDragging = false;
    Wattson::Vector2f m_vecDragPosition = {};
    Wattson::Vector2f m_vecClickPosition = {};
};
