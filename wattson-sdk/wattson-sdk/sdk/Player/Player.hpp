#pragma once
#include <sdk/InventoryPlayer/InventoryPlayer.hpp>

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

	float MoveForward();

	float MoveStrafe();

	double GetMotionX();

	double GetMotionY();
	
	double GetMotionZ();

	void SetMotionX(double m_dNewMotion);
	
	void SetMotionY(double m_dNewMotion);

	void SetMotionZ(double m_dNewMotion);

	int HurtResistantTime();

	InventoryPlayer GetInventory();
private:
	jobject m_pObject;

	double GetX();

	double GetY();

	double GetZ();

	double GetLastTickPosX();

	double GetLastTickPosY();

	double GetLastTickPosZ();
};