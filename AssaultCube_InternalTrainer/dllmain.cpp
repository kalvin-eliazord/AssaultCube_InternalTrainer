#include "header.h"

// Pointer of the openGL function
using tWglSwapBuffers = BOOL(__stdcall*)(HDC hDc);
tWglSwapBuffers oWglSwapBuffers;

Hook openGLHook{};

// Gateway used to run stolen bytes
BOOL __stdcall hkWglSwapBuffers(HDC hDc)
{
    // DETOUR 
    if (GetAsyncKeyState(VK_F1) & 1)
    {
        Hook hkUnlimitedRifleAmmo((uintptr_t*)(Offset::ModBaseAddr + Offset::DecAmmo), 7);

        ShellCode::jmpBackAddrRifleAmmo = hkUnlimitedRifleAmmo.GetJmpBackAddr();
        CheatMenu::bUnlimitedRifleAmmo = !CheatMenu::bUnlimitedRifleAmmo;

        // Unlimited Rifle Ammo Detour
        if (CheatMenu::bUnlimitedRifleAmmo)
            hkUnlimitedRifleAmmo.DetourTo((uintptr_t*)ShellCode::UnlimitedRifleAmmo);
        else
            hkUnlimitedRifleAmmo.StopDetour();
    }

    if (GetAsyncKeyState(VK_F2) & 1)
    {
        CheatMenu::bNoBulletDamage = !CheatMenu::bNoBulletDamage;

        // No Bullet Damage Detour
        Hook hkNoBulletDamage((uintptr_t*)(Offset::ModBaseAddr + Offset::DecHp), 5);
        ShellCode::jmpBackAddrNoBulletDmg = hkNoBulletDamage.GetJmpBackAddr();

        if (CheatMenu::bNoBulletDamage)
            hkNoBulletDamage.DetourTo((uintptr_t*)ShellCode::NoBulletDamage);
        else
            hkNoBulletDamage.StopDetour();
    }

    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };


    if (GetAsyncKeyState(VK_F3) & 1)
        CheatMenu::bFreezingHealth = !CheatMenu::bFreezingHealth;

    if (GetAsyncKeyState(VK_F4) & 1)
        CheatMenu::bFreezingRifleAmmo = !CheatMenu::bFreezingRifleAmmo;

    if (GetAsyncKeyState(VK_F5) & 1)
        CheatMenu::bAimbot = !CheatMenu::bAimbot;

    if (CheatMenu::bFreezingHealth)
        localPlayer->m_health = 1337;

    // TO DO : actualWeaponTo1337
    if (CheatMenu::bFreezingRifleAmmo)
        localPlayer->assaultRifleAmmo = 1337;

    if (CheatMenu::bAimbot)
        Aimbot::RunAimbot();

    Sleep(5);

    return oWglSwapBuffers(hDc);
}

DWORD WINAPI mainHackThread(HMODULE hModule)
{
    // Create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << ">> Assault Cube Internal Hack by Kalvin << \n";
      // TRAMPOLINE HOOK
    HMODULE hOpenGL32{ GetModuleHandleW(L"opengl32.dll") };
    if (hOpenGL32)
    {
        uintptr_t* wglSwapBuffersAddr{ (uintptr_t*)GetProcAddress(hOpenGL32, "wglSwapBuffers") };
        openGLHook.SetSrc(wglSwapBuffersAddr);
        openGLHook.SetSize(5);

        oWglSwapBuffers = (tWglSwapBuffers) openGLHook.TrampolineHookTo((uintptr_t*)hkWglSwapBuffers);
    }
    //hkUnlimitedRifleAmmo.StopDetour();
    //hkNoBulletDamage.StopDetour();

    if (f)
        fclose(f);

    FreeConsole();
    //FreeLibraryAndExitThread(hModule, 0);

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