#include "header.h"

void MemoryChanger::PatchingByte(uintptr_t* dst, uintptr_t* src, int size)
{
    DWORD oldProtection{};
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtection);

    memcpy(dst, src, size);

    VirtualProtect(dst, size, oldProtection, &oldProtection);
}

void MemoryChanger::NopByte(uintptr_t* dst, int size)
{
    BYTE* nopArray = new BYTE[size];
    memset(nopArray, 0x90, size);

    PatchingByte(dst, (uintptr_t*)nopArray, size);

    delete[] nopArray;
}