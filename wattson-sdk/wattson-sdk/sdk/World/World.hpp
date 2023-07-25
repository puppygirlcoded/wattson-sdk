#pragma once
#include <chrono>

class World
{
public:
	jclass GetClass();
	jobject GetInstance();

	std::vector<Player> GetPlayerEntites();
};

inline auto g_World = std::make_unique<World>();