#pragma once
#include <string>
#include <chrono>
#include <map>

struct AnimationContext_t {
    float m_flValue;
    size_t m_uIdentifier;
};

class AnimationManager
{
public:
    AnimationContext_t Get(const std::string& m_sIdentifier, float m_flDefaultInitValue = 1.f);
    void Lerp(const std::string& m_sIdentifier, float m_flDestiniation, float m_flAdditive = 1.f);
    void Set(const std::string& m_sIdentifier, float m_flValue);
};

inline auto g_AnimationManager = std::make_unique<AnimationManager>();
