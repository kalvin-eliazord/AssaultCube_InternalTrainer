#include "header.h"

uintptr_t* EntityManager::GetEntityListBaseAddr()
{
	uintptr_t* entityListBaseAddr{ nullptr };

	constexpr uintptr_t entityListOffset{ 0x10f4f8 };
	
	return entityListBaseAddr = (uintptr_t*) (MemManager::GetModBaseAddr() + entityListOffset);
}

Player* EntityManager::GetEntity(int iEntity)
{
	Player* entity{ nullptr };

	return entity = *(Player**) (*GetEntityListBaseAddr() + iEntity * 4) ;
}

int* EntityManager::GetNumberOfPlayer()
{
	constexpr uintptr_t nbOfPlayerOffset{ 0x10f500 };

	return (int*)(MemManager::GetModBaseAddr() + nbOfPlayerOffset);
}

bool EntityManager::IsValid(Player* pEntity)
{
	// is entity dead
	if (pEntity->m_health <= 0)
		return false;

	// is entity same team as LocalPlayer
	if (pEntity->teamID == MemManager::GetLocalPlayer()->teamID)
		return false;

	// is entity not loaded
	if (!pEntity or *(uintptr_t*) pEntity == 0x4E1A04)
		return false;

	//is entity behind wall

	return true;
}