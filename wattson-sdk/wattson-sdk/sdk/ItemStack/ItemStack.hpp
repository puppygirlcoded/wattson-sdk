#pragma once

class ItemStack
{
public:
	ItemStack(jobject m_Object) : m_pObject(m_Object) {}

	jobject GetInstance() { return m_pObject; }

	jobject Get();

	bool IsWeapon();
	
	bool IsTool();
	
	bool IsEnderPearl();
	
	bool IsBlock();

private:
	jobject m_pObject;
};