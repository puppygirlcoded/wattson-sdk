#pragma once
#include <chrono>

class Movement
{
public:
	void OnUpdate();
private:
	void KnockbackModifier();
};

inline auto g_Movement = std::make_unique<Movement>();