#include "Weapon.h"

Weapon::Weapon(FString name, int damage)
{
	Name = name;
	Damage = damage;
}

FString Weapon::GetName()
{
	return Name;
}
