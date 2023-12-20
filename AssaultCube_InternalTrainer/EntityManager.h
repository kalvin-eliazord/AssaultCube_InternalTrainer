#pragma once
namespace EntityManager
{
	Entity* GetLocalPlayerPtr();
	uintptr_t* GetEntityListPtr();
	Entity* GetEntityPtr(int iteratorEnt);
	bool IsValid(Entity* pEntity);
	Entity* GetEntityCrossHair();
	int* GetNumberOfPlayerPtr();
};