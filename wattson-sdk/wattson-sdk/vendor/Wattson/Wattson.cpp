#include <vendor/std.hpp>

void WattsonClient::OnStartup()
{
	g_Console->Setup("Wattson debug");

	this->g_Utils.m_pGameWindow = FindWindowA("LWJGL", nullptr);
	if (!this->g_Utils.m_pGameWindow) 
	{
		g_Console->Print("Couldn't get game window!\n");
		return;
	}

	g_Java->OnStartup();

	g_Input->OnStartup();

	g_Mapper->OnStartup();

	g_HookManager->OnStartup();
}

void WattsonClient::OnDestroy()
{
	g_Java->OnDestroy();
	g_Console->Destroy();
	g_HookManager->Destroy();
	g_ClickGui->Destroy();
}

Player WattsonClient::GetLocalPlayer()
{
	return Player::Player();
}

void WattsonClient::OnSwapBuffers()
{
	this->g_Utils.m_vecScreenSize = Vector2f(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
}