#pragma once
namespace EntityManager
{
	Player* GetEntity(int iEntity);
	bool IsValid(Player* pEntity);
	uintptr_t* GetEntityListBaseAddr();
	int* GetNumberOfPlayer();
};