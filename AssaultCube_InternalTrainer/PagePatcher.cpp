#include "header.h"

void PagePatcher::PatchingPage(uintptr_t* pSrc, uintptr_t* pDst, int pSize)
{
    DWORD oldProtection{};
    VirtualProtect(pSrc, pSize, PAGE_EXECUTE_READWRITE, &oldProtection);

    memcpy(pSrc, pDst, pSize);

    VirtualProtect(pSrc, pSize, oldProtection, &oldProtection);
}

void PagePatcher::NopPage(uintptr_t* pSrc, int pSize)
{
    BYTE* nopArray = new BYTE[pSize];
    memset(nopArray, 0x90, pSize);

    PatchingPage(pSrc, (uintptr_t*)nopArray, pSize);

    delete[] nopArray;
}