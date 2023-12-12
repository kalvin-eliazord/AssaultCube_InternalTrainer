#pragma once
class Hook
{
private:
	uintptr_t* src{};
	uintptr_t* stolenBytes{nullptr};
	int size{};

public:
	Hook(uintptr_t* pSrc, const int pSize);
	Hook();

	uintptr_t* GetSrc();
	int GetSize();
	void SetSrc(uintptr_t* pSrc);
	void SetSize(int pSize);
	uintptr_t* TrampolineHookTo(uintptr_t* pDst);
	void DetourTo(uintptr_t* pDst);
	void StopDetour();
	uintptr_t GetJmpBackAddr();
};