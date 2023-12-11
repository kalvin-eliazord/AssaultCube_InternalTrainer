#include "header.h"

Hook::Hook(uintptr_t* pSrc, const int pSize = 5)
    : src{ pSrc }
    , size{ pSize }
{}

Hook::Hook()
{}

/*
Hook::~Hook()
{
    this->StopDetour();
    delete this->src;
}
*/

uintptr_t* Hook::GetSrc()
{
    return this->src;
}

int Hook::GetSize()
{
    return this->size;
}

void Hook::SetSrc(uintptr_t* pSrc)
{
    this->src = pSrc;
}

void Hook::SetSize(int pSize)
{
    this->size = pSize;
}

uintptr_t* Hook::TrampolineHookTo(uintptr_t* pDst)
{
    uintptr_t* gateway{ nullptr };

    DetourTo(pDst);

    gateway = (uintptr_t*)VirtualAlloc(NULL, this->size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if(this->stolenBytes != nullptr)
        memcpy_s(gateway, this->size, this->stolenBytes, this->size);

    constexpr uintptr_t JMP_SYZE{ 5 };
    const uintptr_t gatewayRelativeAddr{ ((uintptr_t)this->src - (uintptr_t)gateway) - JMP_SYZE };

    *(uintptr_t*)((uintptr_t)gateway + this->size) = gatewayRelativeAddr;

    return gateway;
}

void Hook::DetourTo(uintptr_t* pDst)
{
    DWORD oldProtection{};
    VirtualProtect(this->src, this->size, PAGE_EXECUTE_READWRITE, &oldProtection);

    // saving the stolen bytes
    this->stolenBytes = new uintptr_t[this->size];
    memcpy_s(this->stolenBytes, this->size, this->src, this->size);

    // Nop the page
    memset(this->src, 0x90, this->size);

    constexpr uintptr_t JMP_SYZE{ 5 };
    const     uintptr_t dstAddrOffset{ ((uintptr_t)pDst - (uintptr_t)this->src) - JMP_SYZE };

    // writting JMP
    *src = 0xE9;

    // writting addr to jump
    *(uintptr_t*)((uintptr_t)this->src + 1) = dstAddrOffset;

    VirtualProtect(this->src, this->size, oldProtection, &oldProtection);
}

void Hook::StopDetour()
{
    if (this->stolenBytes != nullptr)
    {
        MemoryChanger::PatchingPage(this->src, this->stolenBytes, this->size);
        delete[] this->stolenBytes;
    }
}

uintptr_t Hook::GetJmpBackAddr()
{
    return (uintptr_t) this->src + this->size;
}