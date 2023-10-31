#include "header.h"

uintptr_t MemManager::GetModBaseAddr()
{
	return (uintptr_t)GetModuleHandleW(L"ac_client.exe");
}

uintptr_t* MemManager::GetEntityListBaseAddr()
{
	constexpr uintptr_t entityListOffset{ 0x10f4f8 };
	return (uintptr_t*)(GetModBaseAddr() + entityListOffset);
}

Player* MemManager::GetEntity(int i)
{
	Player* entity{ nullptr };

	for (int i{ 1 }; i < *GetNumberOfPlayer(); ++i)
	{
		 //(GetEntityListBaseAddr() + i) * 4 ;
		
	}

	return entity;
}

int* MemManager::GetNumberOfPlayer()
{
	constexpr uintptr_t nbOfPlayerOffset{ 0x10f500 };
	return (int*)(GetModBaseAddr() + nbOfPlayerOffset);
}

Player* MemManager::GetLocalPlayer()
{
	constexpr uintptr_t localPlayerOffset{ 0x10f4f4 };
	return *(Player**) (GetModBaseAddr() + localPlayerOffset);
}