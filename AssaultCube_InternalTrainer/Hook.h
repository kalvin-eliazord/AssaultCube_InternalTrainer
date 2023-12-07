#pragma once
class Hook
{
private:
	uintptr_t* addrToHook{};
	const int size{};

public:
	Hook(uintptr_t* pAddrToHook, const int pSize);

	bool StartHooking(uintptr_t* myFunc);
	bool StopHooking();
};

static uintptr_t noBulletDmgJmpBack;
void ASM_NoBulletDamage();
static uintptr_t unlimitedRAmmoJmpBack;
void ASM_UnlimitedRifleAmmo();
uintptr_t GetJmpBackAddr(uintptr_t* pAddrToHook, const int pSize = 5);