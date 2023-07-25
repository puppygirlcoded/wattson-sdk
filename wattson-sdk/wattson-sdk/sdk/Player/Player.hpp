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

	float GetHealth();
	float GetMaxHealth();

	bool GetGlowing();
	void SetGlowing(bool m_bNewState);

	std::string GetName();
private:
	jobject m_pObject;

	double GetX();
	double GetY();
	double GetZ();
};