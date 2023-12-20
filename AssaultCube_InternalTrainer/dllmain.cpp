#include "header.h"

// Pointer of the openGL function
using tWglSwapBuffers = BOOL(__stdcall*)(HDC hDc);
tWglSwapBuffers oWglSwapBuffers;
Hook hkOpenGL{};
Hook hkUnlimitedRifleAmmo((uintptr_t*)(Offset::ModBaseAddr + Offset::DecAmmo), 7);
Hook hkNoBulletDamage((uintptr_t*)(Offset::ModBaseAddr + Offset::DecHp), 5);

// wglSwapBuffers function copy to run my code + stolen bytes
BOOL __stdcall hkWglSwapBuffers(HDC hDc)
{
    // Unlimited Rifle Ammo Detour
    if (GetAsyncKeyState(VK_F1) & 1)
    {
        CheatMenu::bUnlimitedRifleAmmo = !CheatMenu::bUnlimitedRifleAmmo;

        if (CheatMenu::bUnlimitedRifleAmmo)
            hkUnlimitedRifleAmmo.DetourTo((uintptr_t*)ShellCode::UnlimitedRifleAmmo);
        else
            hkUnlimitedRifleAmmo.StopDetour();
    }

    // No Bullet Damage Detour
    if (GetAsyncKeyState(VK_F2) & 1)
    {
        CheatMenu::bNoBulletDamage = !CheatMenu::bNoBulletDamage;

        if (CheatMenu::bNoBulletDamage)
            hkNoBulletDamage.DetourTo((uintptr_t*)ShellCode::NoBulletDamage);
        else
            hkNoBulletDamage.StopDetour();
    }

    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };

    // Freezing Health
    if (GetAsyncKeyState(VK_F3) & 1)
        CheatMenu::bFreezingHealth = !CheatMenu::bFreezingHealth;

    if (CheatMenu::bFreezingHealth)
        localPlayer->m_health = 1337;

    // Freezing Rifle Ammo TO DO : actualWeaponTo1337
    if (GetAsyncKeyState(VK_F4) & 1)
        CheatMenu::bFreezingRifleAmmo = !CheatMenu::bFreezingRifleAmmo;

    if (CheatMenu::bFreezingRifleAmmo)
        localPlayer->assaultRifleAmmo = 1337;

    // Aimbot
    if (GetAsyncKeyState(VK_F5) & 1)
        CheatMenu::bAimbot = !CheatMenu::bAimbot;

    if (CheatMenu::bAimbot)
        Aimbot::RunAimbot();

    if (GetAsyncKeyState(VK_F6) & 1)
        CheatMenu::bTriggerBot = !CheatMenu::bTriggerBot;
    
    if (CheatMenu::bTriggerBot)
    {
        Entity* currEntityCrossHair{ EntityManager::GetEntityCrossHair() };

        if (EntityManager::IsValid(currEntityCrossHair))
            *(bool*)((uintptr_t)EntityManager::GetLocalPlayerPtr() + 0x224) = true;
        else
            *(bool*)((uintptr_t)EntityManager::GetLocalPlayerPtr() + 0x224) = false;
    }

    Sleep(5);

    return oWglSwapBuffers(hDc);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    // Create a file to open a writtable console 
    FILE* f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << ">> Assault Cube Internal Hack by Kalvin << \n";

    ShellCode::jmpBackAddrRifleAmmo = hkUnlimitedRifleAmmo.GetJmpBackAddr();
    ShellCode::jmpBackAddrNoBulletDmg = hkNoBulletDamage.GetJmpBackAddr();

     // TRAMPOLINE HOOK
    HMODULE hOpenGL32{ GetModuleHandleW(L"opengl32.dll") };
    if (hOpenGL32)
    {
        // Get "wglSwapBuffers" exported function address
        uintptr_t* wglSwapBuffersAddr{ (uintptr_t*)GetProcAddress(hOpenGL32, "wglSwapBuffers") };

        // Setting openGL address and size for the trampoline hook
        hkOpenGL.SetSrc(wglSwapBuffersAddr);
        hkOpenGL.SetSize(5);

        // Starting the trampoline hook and setting the gateway
        oWglSwapBuffers = (tWglSwapBuffers)hkOpenGL.TrampolineHookTo((uintptr_t*)hkWglSwapBuffers);
    }

    while (!GetAsyncKeyState(VK_DELETE) & 1)
        Sleep(5);

    hkUnlimitedRifleAmmo.StopDetour();
    hkNoBulletDamage.StopDetour();
    hkOpenGL.StopDetour();

    if(f)
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
        HANDLE hackThread{ (CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HackThread), hModule, NULL, nullptr)) };

        if (hackThread)
            CloseHandle(hackThread);
    }

    return TRUE;
}