#include "header.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    // Create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };
    Hook hook{};

    // God mod
    uintptr_t* decHpAddr{ (uintptr_t*)((uintptr_t)GetModuleHandleW(L"ac_client.exe") + Offset::DecHp) };
    uintptr_t  decHpAddrSize{ 5 };
    jmpBackAddr = (*decHpAddr + decHpAddrSize);

    // Nop byte
    uintptr_t* decAmmoAddr    { (uintptr_t*)((uintptr_t)GetModuleHandleW(L"ac_client.exe") + Offset::DecAmmo) };
    uintptr_t  decAmmoAddrSize{2};
    MemoryChanger::NopByte(decAmmoAddr, decAmmoAddrSize);


    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        localPlayer->m_health = 1337;
        // TO DO : actualWeaponTo1337
        localPlayer->assaultRifleAmmo = 1337;

        // If there is no enemy it will crash
        if (*(EntityManager::GetNumberOfPlayerPtr) != 0)
        {
            // TO FIX (mem no allocated)
            //hook.StartHooking(decHpAddr, decHpAddrSize, (uintptr_t*)GodMod_ASM);

            Aimbot::RunAimbot();
        }

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