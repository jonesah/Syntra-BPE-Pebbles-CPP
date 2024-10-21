#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
public:
	int Swing();
	void Throw();
};
