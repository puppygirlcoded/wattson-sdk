#include <vendor/std.hpp>

void HookManager::OnStartup()
{
	if (MH_Initialize() != MH_OK)
	{
		g_Console->Print("Unable to initialise MinHook!\n");
		return;
	}

	if (MH_CreateHookApi(L"opengl32.dll", "wglSwapBuffers", &Detours::SwapBuffers::Hook, reinterpret_cast<void**>(&Detours::SwapBuffers::oSwapBuffers)) != MH_OK) 
	{
		g_Console->Print("Failed to hook opengl32.dll->wglSwapBuffers\n");
		return;
	}
	else 
	{
		g_Console->Print("Hooked opengl32.dll->wglSwapBuffers\n");
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