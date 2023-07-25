#pragma once

class ActiveRenderInfo
{
public:
	Matrix ProjectionMatrix();
	Matrix ModelViewMatrix();
};

inline auto g_ActiveRenderInfo = std::make_unique<ActiveRenderInfo>();