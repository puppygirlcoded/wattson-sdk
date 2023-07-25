#include <vendor/std.hpp>

List::List(jobject m_pObject)
{
	this->m_pObject = m_pObject;
}

jobject List::GetInstance()
{
	return this->m_pObject;
}

jclass List::GetClass()
{
	return g_Java->Enviroment->FindClass("java/util/List");
}

jobjectArray List::Get()
{
	const jmethodID ToArrayID = g_Java->Enviroment->GetMethodID(this->GetClass(), "toArray", "()[Ljava/lang/Object;");
	return reinterpret_cast<jobjectArray>(g_Java->Enviroment->CallObjectMethod(this->GetInstance(), ToArrayID));
}