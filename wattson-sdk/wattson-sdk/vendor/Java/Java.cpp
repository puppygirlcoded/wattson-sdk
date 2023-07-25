#include <vendor/std.hpp>

void Java::OnStartup() {
	jsize m_sCount;
	if (JNI_GetCreatedJavaVMs(&this->VirtualMachine, 1, &m_sCount) != JNI_OK || m_sCount == 0) {
		g_Console->Print("Couldn't get virtual machine instance!\n");
		return;
	}

	jint m_iResult = this->VirtualMachine->GetEnv((void**)&this->Enviroment, JNI_VERSION_1_6);
	if (m_iResult == JNI_EDETACHED) {
		m_iResult = this->VirtualMachine->AttachCurrentThread((void**)&this->Enviroment, nullptr);
	}

	if (this->Enviroment) {
		g_Console->Print("Java instance initialised!\n");
		this->m_bCanRunModules = true;
	}
}

void Java::OnDestroy() {
	this->m_bCanRunModules = false;
}

bool Java::CanRun() {
	const bool m_bCanRun = this->Enviroment && 
						   this->m_bCanRunModules && 
						   g_Minecraft->GetInstance() && 
						   g_World->GetInstance() && 
						   g_Wattson->GetLocalPlayer().GetInstance();

	return m_bCanRun;
}