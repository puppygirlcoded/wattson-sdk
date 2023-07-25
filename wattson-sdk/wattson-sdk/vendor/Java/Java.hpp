#pragma once
#include <chrono>

class Java 
{
public:
	JNIEnv* Enviroment;
	
	void OnStartup();
	void OnDestroy();
	bool CanRun();

private:
	JavaVM* VirtualMachine;

	bool m_bCanRunModules = false;
};

inline auto g_Java = std::make_unique<Java>();