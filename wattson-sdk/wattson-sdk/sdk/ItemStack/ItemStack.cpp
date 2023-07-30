#include <vendor/std.hpp>

jobject ItemStack::Get()
{
    const jclass m_cItemStack = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemStack").data());
    const jmethodID getItemID = g_Java->Enviroment->GetMethodID(m_cItemStack, g_Mapper->GetObsfucatedName("getItem").data(), g_Mapper->GetObsfucatedName("net/minecraft/item/Item", ENameCaseBracketL).data());

    return g_Java->Enviroment->CallObjectMethod(this->m_pObject, getItemID);
}

bool ItemStack::IsWeapon()
{
    const jclass m_cItemSword = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemSword").data());
    const jclass m_cItemAxe = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemAxe").data());

    return g_Java->Enviroment->IsInstanceOf(this->Get(), m_cItemSword) || g_Java->Enviroment->IsInstanceOf(this->Get(), m_cItemAxe);
}

bool ItemStack::IsTool()
{
    const jclass m_cItemTool = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemTool").data());

    return g_Java->Enviroment->IsInstanceOf(this->Get(), m_cItemTool);
}

bool ItemStack::IsEnderPearl()
{
    const jclass m_cItemEnderPearl = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemEnderPearl").data());

    return g_Java->Enviroment->IsInstanceOf(this->Get(), m_cItemEnderPearl);
}

bool ItemStack::IsBlock()
{
    const jclass m_cItemBlock = g_Java->Enviroment->FindClass(g_Mapper->GetObsfucatedName("net/minecraft/item/ItemBlock").data());

    return g_Java->Enviroment->IsInstanceOf(this->Get(), m_cItemBlock);
}