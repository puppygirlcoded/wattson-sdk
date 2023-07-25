#include <vendor/std.hpp>

void HookManager::OnStartup()
{
	if (MH_Initialize() != MH_OK)
	{
		g_Console->Print("Unable to initialise MinHook!\n");
		return;
	}

	if (MH_CreateHookApi(L"Gdi32.dll", "SwapBuffers", &Detours::SwapBuffers::Hook, reinterpret_cast<void**>(&Detours::SwapBuffers::oSwapBuffers)) != MH_OK) 
	{
		g_Console->Print("Failed to hook Gdi32.dll->SwapBuffers\n");
		return;
	}
	else 
	{
		g_Console->Print("Hooked Gdi32.dll->SwapBuffers\n");
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) 
	{
		g_Console->Print("Failed to intialise MH hooks!\n");
		return;
	}

	g_Console->Print("Hooks initalised!\n");
}

void HookManager::Destroy()
{
	MH_DisableHook(MH_ALL_HOOKS);
}