#include <vendor/std.hpp>

int InventoryPlayer::GetActiveSlot()
{
	const jclass m_cInventoryPlayer = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/entity/player/InventoryPlayer").data());
	const jfieldID currentItemID = g_Java->Enviroment->GetFieldID(m_cInventoryPlayer, g_Mapper->GetObsfucatedName("currentItem").data(), "I");
	
	return g_Java->Enviroment->GetIntField(this->GetInstance(), currentItemID);
}

void InventoryPlayer::SetActiveSlot(const int m_iNewSlot)
{
	const jclass m_cInventoryPlayer = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/entity/player/InventoryPlayer").data());
	const jfieldID currentItemID = g_Java->Enviroment->GetFieldID(m_cInventoryPlayer, g_Mapper->GetObsfucatedName("currentItem").data(), "I");

	g_Java->Enviroment->SetIntField(this->GetInstance(), currentItemID, m_iNewSlot);
}

ItemStack InventoryPlayer::GetItemFromSlot(const int m_iSlot)
{
	const jclass m_cInventoryPlayer = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/entity/player/InventoryPlayer").data());
	const std::string m_sItemStackSignature = std::vformat("(I){}", std::make_format_args(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemStack", ENameCaseL)));
	const jmethodID getStackInSlotID = g_Java->Enviroment->GetMethodID(m_cInventoryPlayer, g_Mapper->GetObsfucatedName("getStackInSlot").data(), m_sItemStackSignature.data());

	return ItemStack(g_Java->Enviroment->CallObjectMethod(this->GetInstance(), getStackInSlotID, m_iSlot));
}