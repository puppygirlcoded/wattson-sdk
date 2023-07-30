#include <vendor/std.hpp>

void FastPlace::OnUpdate()
{
	if (!g_Vars->Helpers.FastPlace)
	{
		return;
	}

	auto Inventory = g_Wattson->GetLocalPlayer().GetInventory();
	if (!Inventory.GetInstance())
	{
		return;
	}

	auto HeldItem = Inventory.GetItemFromSlot(Inventory.GetActiveSlot());
	if (!HeldItem.GetInstance())
	{
		return;
	}

	g_Minecraft->SetRightClickDelay(HeldItem.IsBlock() ? 1 : 6);
}