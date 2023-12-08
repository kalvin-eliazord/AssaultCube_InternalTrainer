#pragma once
class Hook
{
private:
	uintptr_t* src{};
	uintptr_t* stolenBytes{nullptr};
	const int size{};

public:
	void ASM_NoBulletDamage();
	void ASM_UnlimitedRifleAmmo();
	Hook(uintptr_t* pSrc, const int pSize);
	~Hook();

	uintptr_t* GetSrc();
	int GetSize();
	void DetourTo(uintptr_t* pDst);
	void StopDetour();
	uintptr_t GetJmpBackAddr();
};