#include <vendor/std.hpp>

jobject Player::GetInstance()
{
	return this->m_pObject;
}

jclass Player::GetClass()
{
	return g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/entity/EntityPlayerSP").data());
}

jobject Player::GetLocalPlayerObject()
{
	const std::string m_sThePlayerSignature = g_Mapper->GetObsfucatedName("net/minecraft/client/entity/EntityPlayerSP", ENameCaseL);
	const jfieldID thePlayerID = g_Java->Enviroment->GetFieldID(g_Minecraft->GetClass(), g_Mapper->GetObsfucatedName("thePlayer").data(), m_sThePlayerSignature.c_str());
	const jobject m_pPlayerObject = g_Java->Enviroment->GetObjectField(g_Minecraft->GetInstance(), thePlayerID);

	return m_pPlayerObject;
}

// Grabs local player
Player::Player()
{
	const std::string m_sThePlayerSignature = g_Mapper->GetObsfucatedName("net/minecraft/client/entity/EntityPlayerSP", ENameCaseL);
	const jfieldID thePlayerID = g_Java->Enviroment->GetFieldID(g_Minecraft->GetClass(), g_Mapper->GetObsfucatedName("thePlayer").data(), m_sThePlayerSignature.c_str());
	const jobject m_pPlayerObject = g_Java->Enviroment->GetObjectField(g_Minecraft->GetInstance(), thePlayerID);

	this->m_pObject = m_pPlayerObject;
}

Player::Player(jobject m_pObject)
{
	this->m_pObject = m_pObject;
}

double Player::GetX()
{
	const jfieldID posXID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("posX").data(), "D");
	return g_Java->Enviroment->GetDoubleField(this->GetInstance(), posXID);
}

double Player::GetY()
{
	const jfieldID posYID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("posY").data(), "D");
	return g_Java->Enviroment->GetDoubleField(this->GetInstance(), posYID);
}

double Player::GetZ()
{
	const jfieldID posZID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("posZ").data(), "D");
	return g_Java->Enviroment->GetDoubleField(this->GetInstance(), posZID);
}

Vector3f Player::GetOrigin()
{
	return Vector3f(static_cast<float>(this->GetX()), static_cast<float>(this->GetY()), static_cast<float>(this->GetZ()));
}

float Player::GetHealth()
{
	const jclass m_cEntityLivingBase = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/entity/EntityLivingBase").data());
	const jmethodID getHealthID = g_Java->Enviroment->GetMethodID(m_cEntityLivingBase, g_Mapper->GetObsfucatedName("getHealth").data(), "()F");

	if (!getHealthID)
	{
		return -1.f;
	}

	return g_Java->Enviroment->CallFloatMethod(this->GetInstance(), getHealthID);
}

float Player::GetMaxHealth()
{
	const jclass m_cEntityLivingBase = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/entity/EntityLivingBase").data());
	const jmethodID getMaxHealthID = g_Java->Enviroment->GetMethodID(m_cEntityLivingBase, g_Mapper->GetObsfucatedName("getMaxHealth").data(), "()F");

	if (!getMaxHealthID)
	{
		return -1.f;
	}

	return g_Java->Enviroment->CallFloatMethod(this->GetInstance(), getMaxHealthID);
}

bool Player::GetGlowing()
{
	if (g_Wattson->g_Utils.m_iMinecraftVersion != 1)
	{
		return false;
	}

	const jfieldID glowingID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("glowing").data(), "Z");
	return g_Java->Enviroment->GetBooleanField(this->GetInstance(), glowingID);
}

void Player::SetGlowing(bool m_bNewState)
{
	if (g_Wattson->g_Utils.m_iMinecraftVersion != 1)
	{
		return;
	}

	const jfieldID glowingID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("glowing").data(), "Z");
	g_Java->Enviroment->SetBooleanField(this->GetInstance(), glowingID, m_bNewState);
}

std::string Player::GetName()
{
	const jmethodID getNameMethod = g_Java->Enviroment->GetMethodID(this->GetClass(), g_Mapper->GetObsfucatedName("getName").data(), "()Ljava/lang/String;");
	
	const jstring m_jstrName = (jstring)g_Java->Enviroment->CallObjectMethod(this->GetInstance(), getNameMethod);
	const char* m_sNativeString = g_Java->Enviroment->GetStringUTFChars(m_jstrName, nullptr);
	g_Java->Enviroment->ReleaseStringUTFChars(m_jstrName, m_sNativeString);

	return m_sNativeString;
}