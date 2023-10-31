#include "header.h"

uintptr_t MemManager::GetModBaseAddr()
{
	return (uintptr_t)GetModuleHandleW(L"ac_client.exe");
}

Player* MemManager::GetLocalPlayer()
{
	constexpr uintptr_t localPlayerOffset{ 0x10f4f4 };
	return *(Player**) (GetModBaseAddr() + localPlayerOffset);
}