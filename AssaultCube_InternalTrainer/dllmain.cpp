#include "header.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    // create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    // start DETOUR //
    BYTE*     decHpAddr    { (BYTE*)(GetModuleHandleW(L"ac_client.exe") + Offset::DecHp) };
    uintptr_t decHpAddrSize{ 5 };

    // NEED TO CREATE A CLASS OF HOOKING CUZ I NEED MULTIPLE JMPBACKADDR TO BE STORED FOR EACH DETOUR
    MemoryChanger::jmpBackAddr = (uintptr_t)decHpAddr + decHpAddrSize;

    if(!MemoryChanger::Hook(decHpAddr, decHpAddrSize, (BYTE*)MemoryChanger::GodMod_ASM))
        return -1;
    // end DETOUR // 

    // Nop byte
    BYTE*     decAmmoAddr    { (BYTE*)(GetModuleHandleW(L"ac_client.exe") + Offset::DecAmmo) };
    uintptr_t decAmmoAddrSize{2};
    MemoryChanger::NopByte(decAmmoAddr, decAmmoAddrSize);

    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };
    localPlayer->m_health         = 1337;
    localPlayer->assaultRifleAmmo = 1337;
    localPlayer->magPistolAmmo    = 1337;

    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
        Aimbot::RunAimbot();

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