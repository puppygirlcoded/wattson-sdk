#include <vendor/std.hpp>

Vector4f Math::MultiplyMatrix(const Vector4f& v, const Matrix& m)
{
	return Vector4f {
		v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
		v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
		v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
		v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33
	};
}

bool Math::WorldToScreen(const Vector3f& m_vecPoint, Vector2f& m_vecScreen) {
	const auto m_mProjectionMatrix = g_ActiveRenderInfo->ProjectionMatrix();
	const auto m_mModelViewMatrix = g_ActiveRenderInfo->ModelViewMatrix();

	Vector4f csp = MultiplyMatrix(
		MultiplyMatrix(
			Vector4f{ m_vecPoint.x, m_vecPoint.y, m_vecPoint.z, 1.0f },
			m_mModelViewMatrix
		),
		m_mProjectionMatrix
	);

	Vector3f ndc{
		csp.x / csp.w,
		csp.y / csp.w,
		csp.z / csp.w
	};

	if (ndc.z > 1 && ndc.z < 1.15) {
		m_vecScreen = Vector2f{
			((ndc.x + 1.0f) / 2.0f) * g_Wattson->g_Utils.m_vecScreenSize.x,
			((1.0f - ndc.y) / 2.0f) * g_Wattson->g_Utils.m_vecScreenSize.y,
		};
		return true;
	}

	return false;
}