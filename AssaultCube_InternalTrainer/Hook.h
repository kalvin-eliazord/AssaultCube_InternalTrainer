#pragma once
class Hook
{
private:
	uintptr_t* src{};
	uintptr_t* stolenBytes{nullptr};
	const int size{};

public:
	Hook(uintptr_t* pSrc, const int pSize);
	~Hook();

	uintptr_t* GetSrc();
	int GetSize();
	uintptr_t* TrampolineHook(uintptr_t* pDst);
	void DetourTo(uintptr_t* pDst);
	void StopDetour();
	uintptr_t GetJmpBackAddr();
};