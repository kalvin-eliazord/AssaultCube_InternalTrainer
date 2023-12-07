#include "header.h"

// TODO: trampoline hook 
using twglSwapBuffers = BOOL(__stdcall*)(HDC hDc);

twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
    std::cout << "Swapbuffer hooked! \n";
    return owglSwapBuffers(hDc);
}

void __declspec(naked) ASM_NoBulletDamage()
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
        jmp [noBulletDmgJmpBack]
    }
}

void __declspec(naked) ASM_UnlimitedRifleAmmo()
{
    __asm
    {
        mov eax, [0x50f4f4]
        add eax, 0x150
        cmp esi, eax
        jne originalcode
        //instruction to decrement ammo is removed if localPlayer shooting
        push edi
        mov edi, [esp + 14]
        jmp [unlimitedRAmmoJmpBack]
        originalcode :
        dec[esi]
        push edi
        mov edi, [esp + 14]
        jmp [unlimitedRAmmoJmpBack]
    }
}

uintptr_t GetJmpBackAddr( uintptr_t* pAddrToHook, const int pSize)
{
    if (pSize < 5)
        return NULL;

    return (uintptr_t)pAddrToHook + (uintptr_t)pSize;
}

Hook::Hook(uintptr_t* pAddrToHook, const int pSize = 5)
    : addrToHook{ pAddrToHook }
    , size{ pSize }
{}

bool Hook::StartHooking(uintptr_t* myFunc)
{
    DWORD currProtection{};
    VirtualProtect(this->addrToHook, this->size, PAGE_EXECUTE_READWRITE, &currProtection);

    memset(this->addrToHook, 0x90, this->size);

    //overwrite to JMP 
    *addrToHook = 0xE9;

    constexpr uintptr_t jmpSyze{ 5 };
    const     uintptr_t addrToJump{ ((uintptr_t)myFunc - (uintptr_t)this->addrToHook) - jmpSyze };

    *(uintptr_t*)(this->addrToHook + 1) = addrToJump;

    VirtualProtect(this->addrToHook, this->size, currProtection, &currProtection);

    return true;
}