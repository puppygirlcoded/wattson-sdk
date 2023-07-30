#include <vendor/std.hpp>

void Movement::OnUpdate()
{
	this->KnockbackModifier();
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