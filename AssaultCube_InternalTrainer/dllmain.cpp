#include "header.h"

uintptr_t jmpBackAddrNoBulletDmg{};
void __declspec(naked) ASM_NoBulletDamage()
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

uintptr_t jmpBackAddrRifleAmmo{};
void __declspec(naked) ASM_UnlimitedRifleAmmo()
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

// Pointer of the openGL function
using tWglSwapBuffers = BOOL(__stdcall*)(HDC hDc);
tWglSwapBuffers oWglSwapBuffers;

// Gateway used to run stolen bytes
BOOL __stdcall hkWglSwapBuffers(HDC hDc)
{
    std::cout << "Swapbuffer hooked! \n";
    return oWglSwapBuffers(hDc);
}

DWORD WINAPI mainHackThread(HMODULE hModule)
{
    // Create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << ">> Assault Cube Internal Hack by Kalvin << \n";

    // Cheats available
    bool bNoBulletDamage{ false };
    bool bUnlimitedRifleAmmo{ false };
    bool bFreezingHealth{ false };
    bool bFreezingRifleAmmo{ false };
    bool bAimbot{ false };

    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };

    // DETOUR 
    // No Bullet Damage Detour
    Hook hkNoBulletDamage((uintptr_t*)(Offset::ModBaseAddr + Offset::DecHp),5);
    jmpBackAddrNoBulletDmg = hkNoBulletDamage.GetJmpBackAddr();

    // Unlimited Rifle Ammo Detour
    Hook hkUnlimitedRifleAmmo((uintptr_t*)(Offset::ModBaseAddr + Offset::DecAmmo), 7);
    jmpBackAddrRifleAmmo = hkUnlimitedRifleAmmo.GetJmpBackAddr();

    // TRAMPOLINE HOOK
    Hook tHkwglSwapBuffers((uintptr_t*)GetProcAddress(GetModuleHandleW(L"opengl32.dll"), "wglSwapBuffers"), 6);
    
    oWglSwapBuffers = (tWglSwapBuffers) tHkwglSwapBuffers.TrampolineHook((uintptr_t*)hkWglSwapBuffers);

    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            bUnlimitedRifleAmmo = !bUnlimitedRifleAmmo;

            if (bUnlimitedRifleAmmo)
                hkUnlimitedRifleAmmo.DetourTo((uintptr_t*)ASM_UnlimitedRifleAmmo);
            else
                hkUnlimitedRifleAmmo.StopDetour();
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            bNoBulletDamage = !bNoBulletDamage;

            if (bNoBulletDamage)
                hkNoBulletDamage.DetourTo((uintptr_t*)ASM_NoBulletDamage);
            else
                hkNoBulletDamage.StopDetour();
        }

        if (GetAsyncKeyState(VK_F3) & 1 )
        {
            bFreezingHealth = !bFreezingHealth;
        }

        if (bFreezingHealth)
            localPlayer->m_health = 1337;

        if (GetAsyncKeyState(VK_F4) & 1)
        {
            bFreezingRifleAmmo = !bFreezingRifleAmmo;
        }

        if (bFreezingRifleAmmo)
            localPlayer->assaultRifleAmmo = 1337;

            // TO DO : actualWeaponTo1337

        if (GetAsyncKeyState(VK_F5) & 1)
        {
            bAimbot = !bAimbot;
        }

            if (bAimbot)
                Aimbot::RunAimbot();

        Sleep(5);
    }

    hkUnlimitedRifleAmmo.StopDetour();
    hkNoBulletDamage.StopDetour();

    if (f)
        fclose(f);

    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        HANDLE hackThread{ (CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(mainHackThread), hModule, NULL, nullptr)) };

        if (hackThread)
            CloseHandle(hackThread);
    }

    return TRUE;
}