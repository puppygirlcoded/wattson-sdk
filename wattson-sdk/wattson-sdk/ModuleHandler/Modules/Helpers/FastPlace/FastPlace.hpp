#pragma once
#include <chrono>

class FastPlace
{
public:
	void OnUpdate();
};

inline auto g_FastPlace = std::make_unique<FastPlace>();