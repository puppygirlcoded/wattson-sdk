#pragma once
#include <chrono>

class Variables
{
public:

	struct
	{
		bool Name;
		bool Snaplines;
		bool Glow;

		bool Fullbright;
	} 
	Visuals;
};

inline auto g_Vars = std::make_unique<Variables>();