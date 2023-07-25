#include <vendor/std.hpp>

unsigned long long Startup(void* m_pInstance)
{
	try
	{
		g_Wattson->OnStartup();
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(nullptr, "Error", ex.what(), MB_OK);
		FreeLibraryAndExitThread(static_cast<HMODULE>(m_pInstance), 0);
	}

	while (!GetAsyncKeyState(VK_END))
	{
		g_ModuleHandler->HandleModules();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	g_Wattson->OnDestroy();

	FreeLibraryAndExitThread(static_cast<HMODULE>(m_pInstance), 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  dReason,
	LPVOID lpReserved
)
{
	DisableThreadLibraryCalls(hModule);
	switch (dReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Startup), hModule, 0, nullptr);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

