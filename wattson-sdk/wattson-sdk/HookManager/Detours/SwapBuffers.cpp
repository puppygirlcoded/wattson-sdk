#include <vendor/std.hpp>

void Detours::SwapBuffers::Hook(HDC hdc)
{
	if (!hdc)
	{
		return oSwapBuffers(hdc);
	}

	g_Wattson->g_Utils.m_cGameHDC = hdc;

	g_ClickGui->OnSwapBuffers();

	return oSwapBuffers(hdc);
}