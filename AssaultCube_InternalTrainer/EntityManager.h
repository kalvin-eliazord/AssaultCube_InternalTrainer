#pragma once
namespace EntityManager
{
	Player* GetEntity(int i);
	uintptr_t* GetEntityListBaseAddr();

	int* GetNumberOfPlayer();

	bool IsValid(Player* pEntity);
};