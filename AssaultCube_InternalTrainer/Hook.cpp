#include "header.h"

// TODO: trampoline hook 
using tWglSwapBuffers = BOOL(__stdcall*)(HDC hDc);

tWglSwapBuffers oWglSwapBuffers;

BOOL __stdcall hkWglSwapBuffers(HDC hDc)
{
    std::cout << "Swapbuffer hooked! \n";
    return oWglSwapBuffers(hDc);
}

Hook::Hook(uintptr_t* pSrc, const int pSize = 5)
    : src{ pSrc }
    , size{ pSize }
{}

uintptr_t Hook::GetJmpBackAddr(uintptr_t* pSrc, const int pSize)
{
    if (pSize < 5)
        return NULL;

    return (uintptr_t)this->src + (uintptr_t)this->size;
}

Hook::~Hook()
{
    this->StopDetour();
    delete this->src;
}

uintptr_t* Hook::GetSrc()
{
    return this->src;
}

int Hook::GetSize()
{
    return this->size;
}

void Hook::DetourTo(uintptr_t* pDst)
{
    DWORD oldProtection{};
    VirtualProtect(this->src, this->size, PAGE_EXECUTE_READWRITE, &oldProtection);

    // saving the stolen bytes
    this->stolenBytes = new uintptr_t[this->size];
    memcpy(this->stolenBytes, this->src, this->size);

    // Nop the page
    memset(this->src, 0x90, this->size);

    constexpr uintptr_t jmpSyze{ 5 };
    const     uintptr_t dstAddrOffset{ ((uintptr_t)pDst - (uintptr_t)this->src) - jmpSyze };

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