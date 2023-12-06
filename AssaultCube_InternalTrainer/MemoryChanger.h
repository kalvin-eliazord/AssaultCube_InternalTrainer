#pragma once
namespace MemoryChanger
{
	void GodMod_ASM();
	bool Hook(BYTE* addrToHook, uintptr_t len, BYTE* myFunc);
	void PatchingByte(BYTE* dst, BYTE* src, BYTE dstSize);
	void NopByte(BYTE* dst, BYTE dstSize);

	static uintptr_t jmpBackAddr{};
};