#include <vendor/std.hpp>

void ModuleHandler::HandleModules()
{
	g_Render->Clear();

	if (!g_Java->CanRun())
	{
		g_Render->Swap();
		return;
	}

	g_FastPlace->OnUpdate();

	g_Visuals->OnUpdate();

	g_Render->Swap();

	g_Clicker->OnUpdate();

	g_Movement->OnUpdate();
}