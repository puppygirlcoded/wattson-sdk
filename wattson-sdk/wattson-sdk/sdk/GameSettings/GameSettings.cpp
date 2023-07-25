#include <vendor/std.hpp>

jobject GameSettings::GetInstance()
{
	auto m_oGameSettings = g_Java->Enviroment->GetFieldID(g_Minecraft->GetClass(), g_Mapper->GetObsfucatedName("gameSettings").data(),
		g_Mapper->GetObsfucatedName("net/minecraft/client/settings/GameSettings", ENameCaseL).data());

	return g_Java->Enviroment->GetObjectField(g_Minecraft->GetInstance(), m_oGameSettings);
}

float GameSettings::GetGamma()
{
	auto m_cGameSettings = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/settings/GameSettings").data());
	auto GammaSettingID = g_Java->Enviroment->GetFieldID(m_cGameSettings, g_Mapper->GetObsfucatedName("gammaSetting").data(), "F");

	return g_Java->Enviroment->GetFloatField(this->GetInstance(), GammaSettingID);
}

void GameSettings::SetGamma(float m_flNewGamma)
{
	auto m_cGameSettings = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/settings/GameSettings").data());
	auto GammaSettingID = g_Java->Enviroment->GetFieldID(m_cGameSettings, g_Mapper->GetObsfucatedName("gammaSetting").data(), "F");

	g_Java->Enviroment->SetFloatField(this->GetInstance(), GammaSettingID, m_flNewGamma);
}