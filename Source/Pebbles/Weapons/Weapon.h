#pragma once

class Weapon
{
public:
	int Damage;
	float Weight = 2.0f;
	int Range = 5;
	Weapon(FString name, int damage);
	FString GetName();
private:
	FString Name;
};
