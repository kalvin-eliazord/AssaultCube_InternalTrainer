#include "header.h"

uintptr_t jmpBackAddr{};
void __declspec(naked) myASMFunc()
{
    __asm
    {
        mov eax, [0x50f4f4]
        add eax, 0xF4
        cmp eax, ebx 
        jne originalCode
        // nullifying damage taken if localPlayer
        mov edi, 0
        originalCode:
        sub [ebx+4], edi
        mov eax, edi
        pop edi
        jmp [jmpBackAddr]
    }
}

bool toHook(BYTE* addrToHook, uintptr_t len, BYTE* myFunc)
{
    if (len < 5)
        return false;

    DWORD currProtection{};

    VirtualProtect(addrToHook, len, PAGE_EXECUTE_READWRITE, &currProtection);

    memset(addrToHook, 0x90, len);

    //overwrite to JMP 
    *addrToHook = 0xE9;

    constexpr uintptr_t jmpSyze{ 5 };
    const uintptr_t addrToJump{ ((uintptr_t)myFunc - (uintptr_t)addrToHook) - jmpSyze };
        
    *(uintptr_t*) (addrToHook + 1) = addrToJump;

    VirtualProtect(addrToHook, len, currProtection, &currProtection);

    return true;
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    // create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    Entity* localPlayer{ EntityManager::GetLocalPlayerAddr()};

    float closestDistance{ 1000000.0f };
    float currentDistance{ NULL };
    int entityDistIndex{ -1 };

    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        // HOOKING //ac_client.exe+29D1F 

        BYTE* addrToHook{ (BYTE*) (MemManager::modBaseAddr + 0x29D1F) };
        uintptr_t hookLen{ 6 };

        jmpBackAddr = (uintptr_t) addrToHook + hookLen;

        if (!toHook(addrToHook, hookLen, (BYTE*)myASMFunc))
            return -1;

        localPlayer->m_health = 1337;
        localPlayer->assaultRifleAmmo = 1337;
        localPlayer->magPistolAmmo = 1337;

        // AIMBOT //
        std::vector<Vector3> DistanceTargetList{};

        // iterate all the entities to find the closest 
        for (int i{ 1 }; i < *EntityManager::GetNumberOfPlayer(); ++i)
        {
            Entity* entity{ EntityManager::GetEntity(i) };

            if (!EntityManager::IsValid(entity))
                continue;

            const Vector3 delta{ Aimbot::GetDelta(entity->m_Coords, localPlayer->m_Coords) };
                
            currentDistance = Aimbot::GetMagnitude(delta);

            if (currentDistance < closestDistance && currentDistance != NULL)
            {
                closestDistance = currentDistance;
                entityDistIndex = i;
            }
        }

        // error, stop the program
        if (entityDistIndex == -1)
            return -1;

        Entity* closestTarget{ EntityManager::GetEntity(entityDistIndex) };
        const Vector3 targetAngle{ Aimbot::CalculateAngles(closestTarget) };

        // right click to shoot at closest target
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            localPlayer->m_Angles.x = targetAngle.x;
            localPlayer->m_Angles.y = targetAngle.y;
        }
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
        CloseHandle(CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HackThread), hModule, NULL, nullptr));

    return TRUE;
}