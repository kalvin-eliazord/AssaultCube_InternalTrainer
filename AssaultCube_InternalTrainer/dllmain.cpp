#include "header.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    // Create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };

    // No Bullet Damage
    uintptr_t* decHpAddr    { (uintptr_t*)(Offset::ModBaseAddr + Offset::DecHp) };
    const uintptr_t decHpAddrSize{ 5 };
    noBulletDmgJmpBack = GetJmpBackAddr(decHpAddr, decHpAddrSize);
    Hook noBulletDamage(decHpAddr, decHpAddrSize);
    noBulletDamage.StartHooking((uintptr_t*)ASM_NoBulletDamage);

    // Unlimited Rifle Ammo
    uintptr_t* decAmmoAddr { (uintptr_t*)(Offset::ModBaseAddr + Offset::DecAmmo) };
    const uintptr_t decAmmoAddrSize{2};
    unlimitedRAmmoJmpBack = GetJmpBackAddr(decHpAddr, decHpAddrSize);
    Hook unlimitedRifleAmmo(decAmmoAddr, decAmmoAddrSize);
    unlimitedRifleAmmo.StartHooking((uintptr_t*)ASM_UnlimitedRifleAmmo);

    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        localPlayer->m_health = 1337;
        // TO DO : actualWeaponTo1337
        localPlayer->assaultRifleAmmo = 1337;

        Aimbot::RunAimbot();
        Sleep(5);
    }

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
        HANDLE hackThread{ (CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HackThread), hModule, NULL, nullptr)) };

        if (hackThread)
            CloseHandle(hackThread);
    }

    return TRUE;
}