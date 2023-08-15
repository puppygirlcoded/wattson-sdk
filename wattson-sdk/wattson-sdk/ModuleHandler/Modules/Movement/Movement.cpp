#include <vendor/std.hpp>

void Movement::OnUpdate()
{
	this->KnockbackModifier();
	this->FastStop();
}

void Movement::KnockbackModifier()
{
	if (!g_Vars->Movement.KnockbackModifier)
	{
		return;
	}

	if (g_Wattson->GetLocalPlayer().HurtResistantTime() > 0)
	{
		g_Wattson->GetLocalPlayer().SetMotionX(static_cast<double>(g_Wattson->GetLocalPlayer().GetMotionX() * g_Vars->Movement.KnockbackModifierValue));
		g_Wattson->GetLocalPlayer().SetMotionZ(static_cast<double>(g_Wattson->GetLocalPlayer().GetMotionY() * g_Vars->Movement.KnockbackModifierValue));
	}
}

void Movement::FastStop()
{
	if (!g_Vars->Movement.FastStop)
	{
		return;
	}

	// ordered by WASD
	const std::vector<int> m_vecVirtualKeys = { 0x57, 0x41, 0x53, 0x44 };

	if (g_Input->IsKeyDown(m_vecVirtualKeys[0]) || 
		g_Input->IsKeyDown(m_vecVirtualKeys[1]) || 
		g_Input->IsKeyDown(m_vecVirtualKeys[2]) || 
		g_Input->IsKeyDown(m_vecVirtualKeys[3]))
	{
		return;
	}

	g_Wattson->GetLocalPlayer().SetMotionX(0.0);
	g_Wattson->GetLocalPlayer().SetMotionZ(0.0);
}