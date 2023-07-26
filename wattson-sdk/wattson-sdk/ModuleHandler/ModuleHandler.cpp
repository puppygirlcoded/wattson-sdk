#include <vendor/std.hpp>

void ModuleHandler::HandleModules()
{
	g_Render->Clear();

	if (!g_Java->CanRun())
	{
		return;
	}

	std::thread([&] { g_Clicker->OnUpdate(); std::this_thread::sleep_for(std::chrono::milliseconds(5)); }).detach();

	g_Visuals->OnUpdate();

	g_Render->Swap();
}