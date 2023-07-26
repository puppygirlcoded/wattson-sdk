#pragma once
#include <string>
#include <shared_mutex>
#include <any>
#include <deque>

#include "../Math/Math.hpp"
#include "../Render/WattsonRender.hpp"
#include "../Other/AnimationManager.hpp"

enum EFormFlags
{
    EFormFlagNone = 0,
    EFormFlagOpenCollapsedState = (1 << 1),
};

enum EControlType
{
    ControlTypeNone = 0,
    ControlTypeLabel,
    ControlTypeCheckbox,
    ControlTypeSliderFloat,
    ControlTypeSliderInt,
};

class Object
{
public:
    void SetObject(const Wattson::Vector2f& m_vecNewObject)
    {
        this->m_vecObject = m_vecNewObject;
    }

    Wattson::Vector2f GetObject()
    {
        return this->m_vecObject;
    }

private:
    Wattson::Vector2f m_vecObject;
};
