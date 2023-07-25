#pragma once

#include <windows.h>
#include <array>
#include <chrono>

enum class EKeyStates : int
{
	EKeyStateNone = 0,
	EKeyStateDown,
	EKeyStateUp,
	EKeyStateReleased
};

long __stdcall WndProc(HWND m_Window, UINT m_uMsg, WPARAM m_wParam, LPARAM m_lParam);

class Input
{
public:
	HWND m_Window = nullptr;
	WNDPROC m_OldWndProc = nullptr;

	std::array< EKeyStates, 256U > m_arrKeyStates = {};

	bool OnStartup();
	void Destroy();
	
	bool OnWndProc(UINT m_uMsg, WPARAM m_wParam, LPARAM m_lParam);

	bool IsKeyDown(const std::uint32_t m_uButtonCode) 
	{
		return this->m_arrKeyStates[m_uButtonCode] == EKeyStates::EKeyStateDown;
	}

	bool IsKeyReleased(const std::uint32_t m_uButtonCode)
	{
		if (this->m_arrKeyStates[m_uButtonCode] == EKeyStates::EKeyStateReleased)
		{
			this->m_arrKeyStates[m_uButtonCode] = EKeyStates::EKeyStateUp;
			return true;
		}

		return false;
	}
};

inline auto g_Input = std::make_unique<Input>();