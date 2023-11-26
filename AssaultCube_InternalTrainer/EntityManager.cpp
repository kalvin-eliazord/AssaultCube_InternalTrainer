#include "header.h"

uintptr_t* EntityManager::GetEntityListBaseAddr()
{
	uintptr_t* entityListBaseAddr{ nullptr };

	constexpr uintptr_t entityListOffset{ 0x10f4f8 };
	
	return entityListBaseAddr = (uintptr_t*) ((uintptr_t)GetModuleHandleW(L"ac_client.exe") + entityListOffset);
}

Entity* EntityManager::GetLocalPlayerAddr()
{
	Entity* localPlayerAddr{ nullptr };

	uintptr_t localPlayerOffset{ 0x10f4f4 };
	uintptr_t modBaseAddr{ (uintptr_t)GetModuleHandleW(L"ac_client.exe") };

	return localPlayerAddr = *(Entity**)(modBaseAddr + localPlayerOffset);
}

Entity* EntityManager::GetEntity(int iEntity)
{
	Entity* entity{ nullptr };

	return entity = *(Entity**) (*EntityManager::GetEntityListBaseAddr() + iEntity * 4) ;
}

int* EntityManager::GetNumberOfPlayer()
{
	constexpr uintptr_t nbOfPlayerOffset{ 0x10f500 };

	return (int*)((uintptr_t)GetModuleHandleW(L"ac_client.exe") + nbOfPlayerOffset);
}

bool EntityManager::IsValid(Entity* pEntity)
{
	// is entity dead
	if (pEntity->m_health <= 0)
		return false;

	// is entity same team as Entity
	if (pEntity->teamID == EntityManager::GetLocalPlayerAddr()->teamID)
		return false;

	// is entity not loaded
	if (!pEntity or *(uintptr_t*) pEntity == 0x4E1A04)
		return false;

	//is entity behind wall

	return true;
}