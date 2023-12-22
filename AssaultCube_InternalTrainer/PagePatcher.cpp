#include "header.h"

void PagePatcher::PatchingPage(uintptr_t* pSrc, uintptr_t* pDst, int pSize)
{
    DWORD oldProtection{};
    VirtualProtect(pSrc, pSize, PAGE_EXECUTE_READWRITE, &oldProtection);

    memcpy(pSrc, pDst, pSize);

    VirtualProtect(pSrc, pSize, oldProtection, &oldProtection);
}