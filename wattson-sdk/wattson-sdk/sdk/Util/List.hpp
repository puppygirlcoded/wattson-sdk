#pragma once

class List
{
public:
	List(jobject m_pObject);

	jobject GetInstance();
	jclass GetClass();

	jobjectArray Get();

private:
	jobject m_pObject;
};