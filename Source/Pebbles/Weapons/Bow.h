#pragma once
#include "ProjectileWeapon.h"

class Bow : public ProjectileWeapon
{
public:
	int StringType;
	void Pull(int Strength);
};
