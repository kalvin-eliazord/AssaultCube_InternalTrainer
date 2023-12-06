#pragma once
namespace MemoryChanger
{
	void PatchingByte(uintptr_t* dst, uintptr_t* src, int size);
	void NopByte(uintptr_t* dst, int size);
};