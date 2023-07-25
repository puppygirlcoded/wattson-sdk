#include <vendor/std.hpp>

void ModuleHandler::HandleModules()
{
	g_Render->Clear();

	if (!g_Java->CanRun())
	{
		return;
	}

	g_Visuals->OnUpdate();

	g_Render->Swap();
}