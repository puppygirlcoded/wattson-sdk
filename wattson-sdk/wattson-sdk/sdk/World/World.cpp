#include <vendor/std.hpp>

jclass World::GetClass()
{
	return g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/multiplayer/WorldClient").data());
}

jobject World::GetInstance()
{
	const std::string m_sTheWorldSignature = g_Mapper->GetObsfucatedName("net/minecraft/client/multiplayer/WorldClient", ENameCaseL).data();
	const jfieldID theWorldID = g_Java->Enviroment->GetFieldID(g_Minecraft->GetClass(), g_Mapper->GetObsfucatedName("theWorld").data(), m_sTheWorldSignature.c_str());

	return g_Java->Enviroment->GetObjectField(g_Minecraft->GetInstance(), theWorldID);
}

std::vector<Player> World::GetPlayerEntites()
{
	std::vector<Player> Ret;

	const jfieldID PlayerEntitiesID = g_Java->Enviroment->GetFieldID(this->GetClass(), g_Mapper->GetObsfucatedName("playerEntities").data(), "Ljava/util/List;");
	const jobject m_pPlayerEntities = g_Java->Enviroment->GetObjectField(this->GetInstance(), PlayerEntitiesID);

	if (!m_pPlayerEntities)
	{
		return Ret;
	}

	const jobjectArray m_arrEntityArray = List::List(m_pPlayerEntities).Get();
	const int m_iSize = g_Java->Enviroment->GetArrayLength(m_arrEntityArray);

	for (int i = 0; i < m_iSize; i++)
	{
		jobject m_pPlayer = g_Java->Enviroment->GetObjectArrayElement(m_arrEntityArray, i);
		if (!m_pPlayer)
		{
			continue;
		}

		Player m_Player = Player::Player(m_pPlayer);
		if (m_Player.IsInvisible())
		{
			continue;
		}
		
		Ret.push_back(m_Player);
	}

	g_Java->Enviroment->DeleteLocalRef(m_pPlayerEntities);
	g_Java->Enviroment->DeleteLocalRef(m_arrEntityArray);

	return Ret;
}