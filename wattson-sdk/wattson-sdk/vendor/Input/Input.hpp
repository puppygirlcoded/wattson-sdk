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

enum class EMouseTypes : DWORD
{
	EMouseTypeLeftUp = WM_LBUTTONUP,
	EMouseTypeLeftDown = WM_LBUTTONDOWN,
	EMouseTypeRightUp = WM_RBUTTONUP,
	EMouseTypeRightDown = WM_RBUTTONDOWN
};

enum class EMouseSides : DWORD
{
	EMouseSideLeft = MK_LBUTTON,
	EMouseSideRight = MK_RBUTTON
};

enum class EMouseButtons : bool 
{ 
	EMouseButtonRight,
	EMouseButtonLeft 

};

enum class EMouseInputTypes : bool 
{ 
	EMouseInputTypeUp, 
	EMouseInputTypeDown 
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

	void SendInput(EMouseTypes m_eType, EMouseSides m_eSide);
	void Click(EMouseInputTypes m_eType, EMouseButtons m_eButton);
};

inline auto g_Input = std::make_unique<Input>();