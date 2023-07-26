#pragma once

class Player
{
public:
	jobject GetInstance();
	jclass GetClass();
	static jobject GetLocalPlayerObject();

	// Grabs the LocalPlayer object
	Player();

	// Sets entity object
	Player(jobject m_pObject);

	Vector3f GetOrigin();
	
	Vector3f GetLastTickOrigin();

	float GetHealth();
	
	float GetMaxHealth();

	bool GetGlowing();
	
	void SetGlowing(bool m_bNewState);

	std::string GetName();
	
	float GetHeight();
	
	bool IsInvisible();
private:
	jobject m_pObject;

	double GetX();
	double GetY();
	double GetZ();

	double GetLastTickPosX();
	double GetLastTickPosY();
	double GetLastTickPosZ();
};