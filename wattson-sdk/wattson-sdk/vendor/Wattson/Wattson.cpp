#include <vendor/std.hpp>

void Wattson::OnStartup()
{
	g_Console->Setup("Wattson debug");

	this->g_Utils.m_pGameWindow = FindWindowA(nullptr, "Minecraft 1.8.9");
	if (!this->g_Utils.m_pGameWindow) 
	{
		this->g_Utils.m_pGameWindow = FindWindowA(nullptr, "Minecraft 1.9.4");
		if (!this->g_Utils.m_pGameWindow)
		{
			g_Console->Print("Couldn't get game window!\n");
			return;
		}
	}

	g_Java->OnStartup();

	g_Input->OnStartup();

	g_Mapper->OnStartup();

	g_HookManager->OnStartup();
}

void Wattson::OnDestroy() 
{
	g_Java->OnDestroy();
	g_Console->Destroy();
	g_HookManager->Destroy();
	g_ClickGui->Destroy();
}

Player Wattson::GetLocalPlayer()
{
	return Player::Player();
}

void Wattson::OnSwapBuffers()
{
	this->g_Utils.m_vecScreenSize = Vector2f(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
}