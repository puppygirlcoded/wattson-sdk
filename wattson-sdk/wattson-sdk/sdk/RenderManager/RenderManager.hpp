#pragma once
#include <chrono>

class RenderManager
{
public:
	jobject GetInstance();
	Vector3f RenderPosition();
};

inline auto g_RenderManager = std::make_unique<RenderManager>();