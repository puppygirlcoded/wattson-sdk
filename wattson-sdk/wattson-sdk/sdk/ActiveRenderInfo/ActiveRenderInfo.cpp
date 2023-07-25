#include <vendor/std.hpp>

Matrix ActiveRenderInfo::ProjectionMatrix()
{
	const auto m_cActiveRenderInfo = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/renderer/ActiveRenderInfo").data());
	const auto projectionID = g_Java->Enviroment->GetStaticFieldID(m_cActiveRenderInfo, g_Mapper->GetObsfucatedName("PROJECTION").data(), "Ljava/nio/FloatBuffer;");
	const auto m_oProjection = g_Java->Enviroment->GetStaticObjectField(m_cActiveRenderInfo, projectionID);

	Matrix m_mProjectionMatrix = FloatBuffer(m_oProjection).GetMatrix();
	g_Java->Enviroment->DeleteLocalRef(m_oProjection);

	return m_mProjectionMatrix;
}

Matrix ActiveRenderInfo::ModelViewMatrix()
{
	const auto m_cActiveRenderInfo = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/client/renderer/ActiveRenderInfo").data());
	const auto modelViewID = g_Java->Enviroment->GetStaticFieldID(m_cActiveRenderInfo, g_Mapper->GetObsfucatedName("MODELVIEW").data(), "Ljava/nio/FloatBuffer;");
	const auto m_oModelView = g_Java->Enviroment->GetStaticObjectField(m_cActiveRenderInfo, modelViewID);

	Matrix m_mModelViewMatrix = FloatBuffer(m_oModelView).GetMatrix();
	g_Java->Enviroment->DeleteLocalRef(m_oModelView);

	return m_mModelViewMatrix;
}
