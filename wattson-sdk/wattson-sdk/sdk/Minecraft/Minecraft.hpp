#pragma once
#include <chrono>

class Minecraft
{
public:
	jobject GetInstance();
	jclass GetClass();
};

inline auto g_Minecraft = std::make_unique<Minecraft>();