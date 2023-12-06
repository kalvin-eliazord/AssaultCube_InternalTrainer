#include "header.h"

// TODO: trampoline hook 
using twglSwapBuffers = BOOL(__stdcall*)(HDC hDc);

twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
    std::cout << "Swapbuffer hooked! \n";
    return owglSwapBuffers(hDc);
}

void __declspec(naked) GodMod_ASM()
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
        jmp [jmpBackAddr]
    }
}

bool Hook::StartHooking(uintptr_t* addrToHook, int size, uintptr_t* myFunc)
{
    if (size < 5)
        return false;

    DWORD currProtection{};
    VirtualProtect(addrToHook, size, PAGE_EXECUTE_READWRITE, &currProtection);

    memset(addrToHook, 0x90, size);

    //overwrite to JMP 
    *addrToHook = 0xE9;

    constexpr uintptr_t jmpSyze{ 5 };
    const     uintptr_t addrToJump{ ((uintptr_t)myFunc - (uintptr_t)addrToHook) - (uintptr_t)jmpSyze };

    *(uintptr_t*)(addrToHook + 1) = addrToJump;

    VirtualProtect(addrToHook, size, currProtection, &currProtection);

    return true;
}
