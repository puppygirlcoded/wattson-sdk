#pragma once
#include <chrono>

class Clicker
{
public:
	void OnUpdate();

private:
	int m_iNextCPS = 0;
};

inline auto g_Clicker = std::make_unique<Clicker>();