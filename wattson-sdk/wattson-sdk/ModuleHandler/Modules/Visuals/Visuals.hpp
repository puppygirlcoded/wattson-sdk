#pragma once

class Visuals
{
public:
	void OnUpdate();
};

inline auto g_Visuals = std::make_unique<Visuals>();