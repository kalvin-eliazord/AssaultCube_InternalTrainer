#pragma once
namespace MemManager
{
	uintptr_t GetModBaseAddr();
	uintptr_t* GetEntityListBaseAddr();

	Player* GetEntity(int i);
	int* GetNumberOfPlayer();
	Player* GetLocalPlayer();
};

