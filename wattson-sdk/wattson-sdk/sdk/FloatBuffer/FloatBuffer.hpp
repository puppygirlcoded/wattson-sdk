#pragma once

class FloatBuffer
{
public:
	FloatBuffer(jobject m_pTargetObject) : m_pObject(m_pTargetObject) {}

	Matrix GetMatrix();
private:
	jobject m_pObject;
};