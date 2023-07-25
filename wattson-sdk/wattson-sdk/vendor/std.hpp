#pragma once

// base windows includes
#include <Windows.h>
#include <windowsx.h>
#include <thread>
#include <string>
#include <map>
#include <deque>
#include <any>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

// libs
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Ws2_32.lib")

// vcpkg / third party includes
#include <Minhook.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_freetype.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl2.h>
#include <GL/gl.h>

// JNI
#include <vendor/JNI/jni.h>
#include <vendor/Java/Java.hpp>

// Console handler
#include <vendor/Console/Console.hpp>

// Version mapper
#include <vendor/Mapper/Mapper.hpp>

// Input handler / manager
#include <vendor/Input/Input.hpp>

// Hook Manager
#include <HookManager/HookManager.hpp>

// Variables
#include <ModuleHandler/Variables.hpp>

// Render manager
#include <vendor/Render/Render.hpp>

// Click Gui
#include <ClickGui/ClickGui.hpp>

// SDK items
#include <vendor/Math/Math.hpp>
#include <sdk/Util/List.hpp>
#include <sdk/FloatBuffer/FloatBuffer.hpp>
#include <sdk/Minecraft/Minecraft.hpp>
#include <sdk/Player/Player.hpp>
#include <sdk/World/World.hpp>
#include <sdk/RenderManager/RenderManager.hpp>
#include <sdk/ActiveRenderInfo/ActiveRenderInfo.hpp>
#include <sdk/GameSettings/GameSettings.hpp>

// Modules
#include <ModuleHandler/Modules/Visuals/Visuals.hpp>

// Module handler
#include <ModuleHandler/ModuleHandler.hpp>

// Wattson handler
#include <vendor/Wattson/Wattson.hpp>