#include <vendor/std.hpp>

#include "Framework/Fonts/Fonts.hpp"

HGLRC m_OriginalContext;
HDC m_MenuHDC;
HGLRC m_MenuContext;

std::atomic_flag m_ClipCursor = ATOMIC_FLAG_INIT;
RECT m_rOriginalClip;

bool m_bIsClickGuiInitialised = false;
void ClickGui::InitClickGui()
{
	if (m_bIsClickGuiInitialised)
	{
		return;
	}

	m_MenuContext = wglCreateContext(g_Wattson->g_Utils.m_cGameHDC);
	wglMakeCurrent(g_Wattson->g_Utils.m_cGameHDC, m_MenuContext);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

	ImFontConfig font_config;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.FontBuilderFlags = 1;
	font_config.FontDataOwnedByAtlas = false;

	static const ImWchar ranges[] = {
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;
	ImGui::GetIO().FontDefault = io.Fonts->AddFontFromMemoryTTF(m_arrInterMediumBinary, sizeof(m_arrInterMediumBinary), 18.f, &font_config, ranges);

	ImGuiFreeType::BuildFontAtlas(io.Fonts);

	ImGui_ImplWin32_Init(g_Wattson->g_Utils.m_pGameWindow);
	ImGui_ImplOpenGL2_Init();

	g_Framework->CreateInstance();

	m_bIsClickGuiInitialised = true;
}

void ClickGui::OnSwapBuffers()
{
	const auto hwnd = WindowFromDC(g_Wattson->g_Utils.m_cGameHDC);
	RECT window_rect; GetClientRect(hwnd, &window_rect);
	m_OriginalContext = wglGetCurrentContext();

	this->InitClickGui();

	wglMakeCurrent(g_Wattson->g_Utils.m_cGameHDC, m_MenuContext);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	g_Wattson->OnSwapBuffers();
	g_Render->OnSwapBuffers();

	ImGui::GetIO().DisplaySize.x = window_rect.right - window_rect.left;
	ImGui::GetIO().DisplaySize.y = window_rect.bottom - window_rect.top;

	ImGui::GetIO().MouseDrawCursor = this->m_bIsOpen;

	static float m_flMenuAlpha = 0.f;
	m_flMenuAlpha = std::clamp<float>(std::lerp(m_flMenuAlpha, static_cast<float>(this->m_bIsOpen), 10.f * ImGui::GetIO().DeltaTime), 0.f, 1.f);

	ImGui::GetStyle().Alpha = m_flMenuAlpha;
	ImGui::GetStyle().WindowRounding = ImGui::GetStyle().ChildRounding = ImGui::GetStyle().FrameRounding = 3.f;

	if (this->m_bIsOpen) 
	{
		if (m_ClipCursor.test_and_set()) 
		{
			GetClipCursor(&m_rOriginalClip);
		}

		ClipCursor(NULL);
	}
	else 
	{
		if (m_rOriginalClip.right > m_rOriginalClip.left && m_rOriginalClip.bottom > m_rOriginalClip.top) 
		{
			ClipCursor(&m_rOriginalClip);
			m_ClipCursor.clear();
		}
	}

	g_WattsonRender->Begin();

	g_Framework->Watermark();

	if (this->m_bIsOpen)
	{
		g_Framework->PollEvents();
	}

	ImGui::Render();

	glClear(256);
	glMatrixMode(5889);
	glOrtho(0.0f, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y, 0.0f, 0.0f, 100.0f);
	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	wglMakeCurrent(g_Wattson->g_Utils.m_cGameHDC, m_OriginalContext);
}

void ClickGui::Destroy()
{
	this->m_bIsOpen = false;
	ImGui::DestroyContext();
}