#include <vendor/std.hpp>

Matrix FloatBuffer::GetMatrix()
{
	const auto m_cFloatBuffer = g_Java->Enviroment->FindClass("java/nio/FloatBuffer");
	const auto getID = g_Java->Enviroment->GetMethodID(m_cFloatBuffer, "get", "(I)F");

	std::vector<float> m_vecMatrix;
	for (int i = 0; i < 16; i++)
	{
		m_vecMatrix.push_back(g_Java->Enviroment->CallFloatMethod(this->m_pObject, getID, i));
	}

	Matrix matrix;

	matrix.m00 = m_vecMatrix[0];
	matrix.m01 = m_vecMatrix[1];
	matrix.m02 = m_vecMatrix[2];
	matrix.m03 = m_vecMatrix[3];
	matrix.m10 = m_vecMatrix[4];
	matrix.m11 = m_vecMatrix[5];
	matrix.m12 = m_vecMatrix[6];
	matrix.m13 = m_vecMatrix[7];
	matrix.m20 = m_vecMatrix[8];
	matrix.m21 = m_vecMatrix[9];
	matrix.m22 = m_vecMatrix[10];
	matrix.m23 = m_vecMatrix[11];
	matrix.m30 = m_vecMatrix[12];
	matrix.m31 = m_vecMatrix[13];
	matrix.m32 = m_vecMatrix[14];
	matrix.m33 = m_vecMatrix[15];

	return matrix;
}