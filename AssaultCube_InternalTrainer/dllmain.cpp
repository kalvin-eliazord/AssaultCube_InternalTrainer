#include "header.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    // create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    Player* localPlayer{ MemManager::GetLocalPlayer()};

    std::cout << *MemManager::GetEntityListBaseAddr << "\n";

    //Hack Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        localPlayer->m_health = 1337;

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
        CloseHandle(CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HackThread), hModule, NULL, nullptr));
    }
    return TRUE;
}