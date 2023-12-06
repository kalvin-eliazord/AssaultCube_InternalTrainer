#include "header.h"

using twglSwapBuffers = BOOL(__stdcall*)(HDC hDc);

twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
    std::cout << "Swapbuffer hooked! \n";
    return owglSwapBuffers(hDc);
}

void __declspec(naked) MemoryChanger::GodMod_ASM()
{
    __asm
    {
        // localPlayer Addr stored in eax
        mov eax, [0x50f4f4]
        add eax, 0xF4
        cmp eax, ebx
        jne originalCode
        // nullifying damage taken if localPlayer
        mov edi, 0
        originalCode:
        sub[ebx + 4], edi
        mov eax, edi
        jmp [MemoryChanger::jmpBackAddr]
    }
}

bool MemoryChanger::Hook(BYTE* addrToHook, uintptr_t len, BYTE* myFunc)
{
    if (len < 5)
        return false;

    DWORD currProtection{};

    VirtualProtect(addrToHook, len, PAGE_EXECUTE_READWRITE, &currProtection);

    memset(addrToHook, 0x90, len);

    //overwrite to JMP 
    *addrToHook = 0xE9;

    constexpr uintptr_t jmpSyze{ 5 };
    const     uintptr_t addrToJump{ ((uintptr_t)myFunc - (uintptr_t)addrToHook) - jmpSyze };

    *(uintptr_t*)(addrToHook + 1) = addrToJump;

    VirtualProtect(addrToHook, len, currProtection, &currProtection);

    return true;
}   

void MemoryChanger::PatchingByte(BYTE* dst, BYTE* src, BYTE dstSize)
{
    DWORD oldProtection{};
    VirtualProtect(dst, dstSize, PAGE_EXECUTE_READWRITE, &oldProtection);

    memcpy(dst, src, dstSize);

    VirtualProtect(dst, dstSize, oldProtection, &oldProtection);
}

void MemoryChanger::NopByte(BYTE* dst, BYTE dstSize)
{
    DWORD oldProtection{};
    VirtualProtect(dst, dstSize, PAGE_EXECUTE_READWRITE, &oldProtection);

    memcpy((BYTE*)dst, (BYTE*)0x90, dstSize);

    VirtualProtect(dst, dstSize, oldProtection, &oldProtection);
}