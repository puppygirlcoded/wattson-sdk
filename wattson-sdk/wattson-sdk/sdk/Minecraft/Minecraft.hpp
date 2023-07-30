#pragma once
#include <chrono>

class Minecraft
{
public:
	jobject GetInstance();
	jclass GetClass();

	void SetRightClickDelay(const int& m_iNewTick);
};

inline auto g_Minecraft = std::make_unique<Minecraft>();