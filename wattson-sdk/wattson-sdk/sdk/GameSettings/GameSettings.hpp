#pragma once

class GameSettings
{
public:
	jobject GetInstance();
	float GetGamma();
	void SetGamma(float m_flNewGamma);
};

inline auto g_GameSettings = std::make_unique<GameSettings>();