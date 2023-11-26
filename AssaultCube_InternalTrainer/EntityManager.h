#pragma once
namespace EntityManager
{
	Entity* GetLocalPlayerAddr();
	uintptr_t* GetEntityListBaseAddr();
	Entity* GetEntity(int iEntity);
	bool IsValid(Entity* pEntity);
	int* GetNumberOfPlayer();
};