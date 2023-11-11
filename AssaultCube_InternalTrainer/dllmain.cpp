#include "header.h"

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

        std::vector<Vector3> DistanceTargetList{};

        float closestDistance{NULL};
        float currentDistance{NULL};
        int entityDistIndex{ -1 };

        // iterate all the entities to find the closest 
        for (int i{ 1 }; i < *EntityManager::GetNumberOfPlayer(); ++i)
        {
            Player* entity{ EntityManager::GetEntity(i) };

            if (!EntityManager::IsValid(entity))
                continue;

            const Vector3 delta{ Aimbot::GetDelta(localPlayer->m_Coords, entity->m_Coords) };
                
            const float currentDistance = Aimbot::GetMagnitude(delta);

            if (currentDistance < closestDistance)
            {
                closestDistance = currentDistance;
                entityDistIndex = i;
            }
        }

        // error, stop the program
        if (entityDistIndex == -1)
            return -1;

        Player* closestTarget{ EntityManager::GetEntity(entityDistIndex) };
        const Vector3 targetAngle{ Aimbot::CalculateAngles(closestTarget) };

        // aim at
   //     if (GetAsyncKeyState(VK_RBUTTON))
 //       {
            localPlayer->m_Angles.x = targetAngle.x;
            localPlayer->m_Angles.y = targetAngle.y;
    //    }
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