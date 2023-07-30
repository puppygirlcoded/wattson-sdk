#pragma once
#include <sdk/ItemStack/ItemStack.hpp>

class InventoryPlayer
{
public:
	InventoryPlayer(jobject m_Object) : m_pObject(m_Object) {}

	jobject GetInstance() { return m_pObject; }

	int GetActiveSlot();

	void SetActiveSlot(const int m_iNewSlot);
	
	ItemStack GetItemFromSlot(const int m_iSlot);
private:
	jobject m_pObject;
};