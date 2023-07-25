#pragma once

namespace Detours
{
	namespace SwapBuffers
	{
		void Hook(HDC hdc);
		inline decltype(&Hook) oSwapBuffers;
	}
}

class HookManager
{
public:
	void OnStartup();
	void Destroy();
};

inline auto g_HookManager = std::make_unique<HookManager>();