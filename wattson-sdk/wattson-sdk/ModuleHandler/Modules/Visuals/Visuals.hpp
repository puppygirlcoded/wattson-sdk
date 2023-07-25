#pragma once

class Visuals
{
public:
	void OnUpdate();
private:
	void Fullbright();
};

inline auto g_Visuals = std::make_unique<Visuals>();