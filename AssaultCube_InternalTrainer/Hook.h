#pragma once
struct Hook
{
	bool StartHooking(uintptr_t* addrToHook, int size, uintptr_t* myFunc);
};

static uintptr_t jmpBackAddr;
void GodMod_ASM();
