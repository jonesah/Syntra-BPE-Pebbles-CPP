#pragma once
#include "Weapon.h"

class ProjectileWeapon : public Weapon
{
public:
	int FireRate;
	int Ammo;


	void Reload();

	void Fire();
	ProjectileWeapon(FString name, int damage, int ammo);

	void SetReloadSpeed(int speed);
private:
	int ReloadSpeed = 3;
};
