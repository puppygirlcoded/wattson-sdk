#include <vendor/std.hpp>

jclass Minecraft::GetClass() 
{
	return g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/Minecraft").data());
}

jobject Minecraft::GetInstance()
{
	if (!this->GetClass()) 
	{
		return nullptr;
	}

	const std::string m_sGetMinecraftSignature = g_Mapper->GetObsfucatedName("net/minecraft/client/Minecraft", ENameCaseBracketL);
	const jmethodID getMinecraftID = g_Java->Enviroment->GetStaticMethodID(this->GetClass(), g_Mapper->GetObsfucatedName("getMinecraft").data(), m_sGetMinecraftSignature.c_str());

	return g_Java->Enviroment->CallStaticObjectMethod(this->GetClass(), getMinecraftID);
}