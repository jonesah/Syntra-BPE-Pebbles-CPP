#include "ProjectileWeapon.h"

void ProjectileWeapon::Reload()
{
	Ammo = 12;
}

void ProjectileWeapon::Fire()
{
	if(Ammo > 0)
	{
		//logic to fire a projectile
		Ammo--;

		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		"Pew. Ammo is now " + FString::FromInt(Ammo));
			
		}
	}
	

	
}

ProjectileWeapon::ProjectileWeapon(FString name, int damage, int ammo): Weapon(name, damage)
{
	Ammo = ammo;
}

void ProjectileWeapon::SetReloadSpeed(int speed)
{
	ReloadSpeed = speed;
}
