#include "header.h"

void __declspec(naked) ShellCode::NoBulletDamage()
{
    __asm
    {
        // localPlayer Addr stored in eax
        mov eax, 0x50f4f4
        // then edi
        mov edi, [eax]
        add edi, 0xF4
        cmp edi, ebx
        jne originalCode
        // nullifying damage taken if localPlayer
        mov edi, 0
        originalCode:
        sub[ebx + 0x4], edi
            mov eax, edi
            jmp[jmpBackAddrNoBulletDmg]
    }
}

void __declspec(naked) ShellCode::UnlimitedRifleAmmo()
{
    __asm
    {
        // load localPlayer
        mov eax, [0x50f4f4]
        //load game logic entity addr into ebx
        lea ebx, [esi]
        // remove the offset of the rifle addr to obtain the lp addr
        sub ebx, 0x150
        // test if this is the localPlayer
        cmp ebx, [eax]
        jne originalcode
        // "dec [esi]" instruction is removed if localPlayer shooting
        push edi
        mov edi, [esp + 0x14]
        jmp[jmpBackAddrRifleAmmo]
        originalcode :
        dec[esi]
            push edi
            mov edi, [esp + 0x14]
            jmp[jmpBackAddrRifleAmmo]
    }
}