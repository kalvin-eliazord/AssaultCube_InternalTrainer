#include "header.h"

bool ShortestDistance(const Vector3 pDst1, const Vector3 pDst2)
{
    return (pDst1 < pDst2);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    // create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    Player* localPlayer{ MemManager::GetLocalPlayer()};

    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        localPlayer->m_health = 1337;
        localPlayer->assaultRifleAmmo = 1337;
        localPlayer->magPistolAmmo = 1337;

        std::vector<Player*> listOfTarget{};

        // iterate all the entities
        for (int i{ 1 }; i < *EntityManager::GetNumberOfPlayer(); ++i)
        {
            Player* entity{ EntityManager::GetEntity(i) };

            if (EntityManager::IsValid(entity))
                listOfTarget.push_back(entity);
        }

        // iterate all the targets
        for(Player* entity : listOfTarget)
        {
            const Vector3 calcAngles{ Aimbot::CalculateAngles(entity) };

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
        CloseHandle(CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HackThread), hModule, NULL, nullptr));
    }
    return TRUE;
}