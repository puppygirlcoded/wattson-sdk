#pragma once
#include <chrono>

class ModuleHandler
{
public:
	void HandleModules();
};

inline auto g_ModuleHandler = std::make_unique<ModuleHandler>();