#include "header.h"

uintptr_t* EntityManager::GetEntityListPtr()
{
	uintptr_t* entityListBaseAddr{ nullptr };
	
	return entityListBaseAddr = (uintptr_t*)((uintptr_t)GetModuleHandleW(L"ac_client.exe") + Offset::EntityList);
}

Entity* EntityManager::GetLocalPlayerPtr()
{
	Entity* localPlayerAddr{ nullptr };

	return localPlayerAddr = *(Entity**)((uintptr_t)GetModuleHandleW(L"ac_client.exe") + Offset::LocalPlayer);
}

Entity* EntityManager::GetEntityPtr(int iteratorEnt)
{
	Entity* entity{ nullptr };

	return entity = *(Entity**) (*EntityManager::GetEntityListPtr() + iteratorEnt * 4) ;
}

int* EntityManager::GetNumberOfPlayerPtr()
{
	return (int*)((uintptr_t)GetModuleHandleW(L"ac_client.exe") + Offset::NbPlayer);
}

bool EntityManager::IsValid(Entity* pEntity)
{
	// is entity dead
	if (pEntity->m_health <= 0)
		return false;

	// is entity same team as Entity
	if (pEntity->teamID == EntityManager::GetLocalPlayerPtr()->teamID)
		return false;

	// is entity not loaded
	if (!pEntity or *(uintptr_t*) pEntity == Offset::EntityNotLoaded)
		return false;

	//is entity behind wall

	return true;
}