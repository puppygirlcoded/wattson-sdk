#include "AnimationManager.hpp"
#include "Utils.hpp"

#include <imgui.h>

std::map<size_t, AnimationContext_t> m_mapAnimationContext;
AnimationContext_t AnimationManager::Get(const std::string& m_sIdentifier, float m_flDefaultInitValue)
{
    auto m_Query = m_mapAnimationContext.find(Hash(m_sIdentifier));
    if (m_Query == m_mapAnimationContext.end())
    {
        m_mapAnimationContext.insert({ Hash(m_sIdentifier), AnimationContext_t{m_flDefaultInitValue, Hash(m_sIdentifier)} });
        m_Query = m_mapAnimationContext.find(Hash(m_sIdentifier));
    }

    return m_Query->second;
}

void AnimationManager::Lerp(const std::string& m_sIdentifier, float m_flDestiniation, float m_flAdditive)
{
    const auto m_mapMapContext = this->Get(m_sIdentifier);
    auto m_Value = m_mapAnimationContext.find(m_mapMapContext.m_uIdentifier);

    m_Value->second.m_flValue = std::lerp(m_Value->second.m_flValue, m_flDestiniation, m_flAdditive * ImGui::GetIO().DeltaTime);
}

void AnimationManager::Set(const std::string& m_sIdentifier, float m_flValue)
{
    const auto m_mapMapContext = this->Get(m_sIdentifier);
    auto m_Value = m_mapAnimationContext.find(m_mapMapContext.m_uIdentifier);

    m_Value->second.m_flValue = m_flValue;
}
