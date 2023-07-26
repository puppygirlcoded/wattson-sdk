#include <vendor/std.hpp>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
long __stdcall WndProc(HWND m_Window, UINT m_uMsg, WPARAM m_wParam, LPARAM m_lParam)
{
	g_Input->OnWndProc(m_uMsg, m_wParam, m_lParam);

	if (g_Input->IsKeyReleased(VK_HOME))
	{
		g_ClickGui->SwitchToggleState();
	}

	if (g_ClickGui->GetToggleState())
	{
		ImGui_ImplWin32_WndProcHandler(m_Window, m_uMsg, m_wParam, m_lParam);
		return 1L;
	}

	return CallWindowProc(g_Input->m_OldWndProc, m_Window, m_uMsg, m_wParam, m_lParam);
}

bool Input::OnStartup()
{
	this->m_Window = g_Wattson->g_Utils.m_pGameWindow;

	if (!this->m_Window)
	{
		return false;
	}

	this->m_OldWndProc = reinterpret_cast<WNDPROC>(
		SetWindowLongPtrW(this->m_Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
}

void Input::Destroy()
{
	if (this->m_OldWndProc) {
		SetWindowLongPtrW(this->m_Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(this->m_OldWndProc));
		this->m_OldWndProc = nullptr;
	}
}

bool Input::OnWndProc(UINT m_uMsg, WPARAM m_wParam, LPARAM m_lParam) 
{
	int m_iCurrentKey = 0;
	EKeyStates m_eCurrentState = EKeyStates::EKeyStateNone;

	switch (m_uMsg) {
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (m_wParam < 256U) 
		{
			m_iCurrentKey = m_wParam;
			m_eCurrentState = EKeyStates::EKeyStateDown;
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (m_wParam < 256U) 
		{
			m_iCurrentKey = m_wParam;
			m_eCurrentState = EKeyStates::EKeyStateUp;
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		m_iCurrentKey = VK_LBUTTON;
		m_eCurrentState = m_uMsg == WM_LBUTTONUP ? EKeyStates::EKeyStateUp : EKeyStates::EKeyStateDown;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		m_iCurrentKey = VK_RBUTTON;
		m_eCurrentState = m_uMsg == WM_RBUTTONUP ? EKeyStates::EKeyStateUp : EKeyStates::EKeyStateDown;
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		m_iCurrentKey = VK_MBUTTON;
		m_eCurrentState = m_uMsg == WM_MBUTTONUP ? EKeyStates::EKeyStateUp : EKeyStates::EKeyStateDown;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_XBUTTONDBLCLK:
		m_iCurrentKey = (GET_XBUTTON_WPARAM(m_wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		m_eCurrentState = m_uMsg == WM_XBUTTONUP ? EKeyStates::EKeyStateUp : EKeyStates::EKeyStateDown;
		break;
	default:
		return false;
	}

	this->m_arrKeyStates[m_iCurrentKey] =
		m_eCurrentState == EKeyStates::EKeyStateUp && this->m_arrKeyStates[m_iCurrentKey] == EKeyStates::EKeyStateDown ? EKeyStates::EKeyStateReleased : m_eCurrentState;

	return true;
}

void Input::SendInput(EMouseTypes m_eType, EMouseSides m_eSide)
{
	POINT m_pPosition = {};
	if (!GetCursorPos(&m_pPosition))
		return;

	const auto m_hCurrentWindow = GetForegroundWindow();
	PostMessage(m_hCurrentWindow, (DWORD)m_eType, (DWORD)m_eSide, MAKELPARAM(m_pPosition.x, m_pPosition.y));
}

void Input::Click(EMouseInputTypes m_eType, EMouseButtons m_eButton)
{
	(bool)(m_eType) ?
		(bool)(m_eButton) ?
		SendInput(EMouseTypes::EMouseTypeLeftDown, EMouseSides::EMouseSideLeft) :
		SendInput(EMouseTypes::EMouseTypeRightDown, EMouseSides::EMouseSideRight) :
		(bool)(m_eButton) ?
		SendInput(EMouseTypes::EMouseTypeLeftUp, EMouseSides::EMouseSideLeft) :
		SendInput(EMouseTypes::EMouseTypeRightDown, EMouseSides::EMouseSideRight);
}