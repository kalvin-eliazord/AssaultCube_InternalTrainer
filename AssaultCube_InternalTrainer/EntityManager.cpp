#include "header.h"

uintptr_t* EntityManager::GetEntityListPtr()
{
	uintptr_t* entityListBaseAddr{ nullptr };
	
	return entityListBaseAddr = (uintptr_t*)(Offset::ModBaseAddr + Offset::EntityList);
}

Entity* EntityManager::GetLocalPlayerPtr()
{
	Entity* localPlayerAddr{ nullptr };

	return localPlayerAddr = *(Entity**)(Offset::ModBaseAddr + Offset::LocalPlayer);
}

Entity* EntityManager::GetEntityPtr(int iteratorEnt)
{
	Entity* entity{ nullptr };

	return entity = *(Entity**) (*EntityManager::GetEntityListPtr() + iteratorEnt * 4) ;
}

int* EntityManager::GetNumberOfPlayerPtr()
{
	return (int*)(Offset::ModBaseAddr + Offset::NbPlayer);
}

bool EntityManager::IsValid(Entity* pEntity)
{
	// is entity not loaded
	if (!pEntity or *(uintptr_t*)pEntity == Offset::EntityNotLoaded)
		return false;

	// is entity dead
	if (pEntity->m_health <= 0)
		return false;

	// is entity same team as Entity
	if (pEntity->teamID == EntityManager::GetLocalPlayerPtr()->teamID)
		return false;

	return true;
}

Entity* EntityManager::GetEntityCrossHair()
{
	uintptr_t* pEntity{NULL};
	uintptr_t getEntityCrossHairFuncAddr{ Offset::ModBaseAddr + 0x607C0 };
	__asm
	{
		sub esp, 7
		call getEntityCrossHairFuncAddr
		mov pEntity, eax
		add esp, 7
	}
	
	return (Entity*)pEntity;
}