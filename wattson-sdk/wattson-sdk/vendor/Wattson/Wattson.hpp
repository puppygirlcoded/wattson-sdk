#pragma once
#include <chrono>

class Wattson 
{
public:
	void OnStartup();
	void OnDestroy();
	void OnSwapBuffers();

	struct Utils {
		HWND m_pGameWindow;
		int m_iMinecraftVersion;
		HDC m_cGameHDC;
		Vector2f m_vecScreenSize;
	} g_Utils;

	Player GetLocalPlayer();
};

inline auto g_Wattson = std::make_unique<Wattson>();