#pragma once
#include <chrono>

class Variables
{
public:

	struct
	{
		bool Enabled = false;
		int MinimumCPS = 5;
		int MaximumCPS = 10;
	}
	Clicker;

	struct
	{
		bool Name;
		bool Box;
		bool Health;
		bool Snaplines;
		bool Glow;

		bool Fullbright;
	} 
	Visuals;
};

inline auto g_Vars = std::make_unique<Variables>();