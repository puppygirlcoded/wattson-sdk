#include <vendor/std.hpp>

jobject RenderManager::GetInstance()
{
	const auto RenderManagerObf = g_Mapper->GetObsfucatedName("net/minecraft/client/renderer/entity/RenderManager", ENameCaseL);
	const auto RenderManagerID = g_Java->Enviroment->GetFieldID(g_Minecraft->GetClass(), g_Mapper->GetObsfucatedName("renderManager").data(), RenderManagerObf.data());

	return g_Java->Enviroment->GetObjectField(g_Minecraft->GetInstance(), RenderManagerID);
}

Vector3f RenderManager::RenderPosition()
{
	const auto m_cRenderManager = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/renderer/entity/RenderManager").data());

	const auto renderPosXID = g_Java->Enviroment->GetFieldID(m_cRenderManager, g_Mapper->GetObsfucatedName("renderPosX").data(), "D");
	const auto renderPosYID = g_Java->Enviroment->GetFieldID(m_cRenderManager, g_Mapper->GetObsfucatedName("renderPosY").data(), "D");
	const auto renderPosZID = g_Java->Enviroment->GetFieldID(m_cRenderManager, g_Mapper->GetObsfucatedName("renderPosZ").data(), "D");

	return Vector3f(
		static_cast<float>(g_Java->Enviroment->GetDoubleField(this->GetInstance(), renderPosXID)),
		static_cast<float>(g_Java->Enviroment->GetDoubleField(this->GetInstance(), renderPosYID)),
		static_cast<float>(g_Java->Enviroment->GetDoubleField(this->GetInstance(), renderPosZID))
	);
}