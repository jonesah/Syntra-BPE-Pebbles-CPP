#pragma once
#include "ProjectileWeapon.h"
class Gun : public ProjectileWeapon
{
public:
	void Clean();
	int Size;
	bool IsDirty;
};
