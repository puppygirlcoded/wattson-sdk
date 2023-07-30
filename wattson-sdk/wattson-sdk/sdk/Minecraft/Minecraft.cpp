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

void Minecraft::SetRightClickDelay(const int& m_iNewTick)
{
	const jfieldID rightClickDelayTimerID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("rightClickDelayTimer").data(), "I");
	g_Java->Enviroment->SetIntField(this->GetInstance(), rightClickDelayTimerID, m_iNewTick);
}