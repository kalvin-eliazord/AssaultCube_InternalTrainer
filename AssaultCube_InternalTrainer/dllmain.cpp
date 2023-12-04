#include "header.h"

using twglSwapBuffers = BOOL (__stdcall *)(HDC hDc);

twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
    std::cout << "Swapbuffer hooked! \n";

    return owglSwapBuffers(hDc);
}

uintptr_t jmpBackAddr{};

void __declspec(naked) GodMod_ASM()
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
        jmp [jmpBackAddr]
    }
}

BYTE* toHook(BYTE* addrToHook, uintptr_t len, BYTE* myFunc)
{
    if (len < 5)
        return nullptr;

    BYTE* savedByte{ nullptr };

    memcpy(savedByte, addrToHook, len);

    DWORD currProtection{};

    VirtualProtect(addrToHook, len, PAGE_EXECUTE_READWRITE, &currProtection);

    memset(addrToHook, 0x90, len);

    //overwrite to JMP 
    *addrToHook = 0xE9;

    constexpr uintptr_t jmpSyze{ 5 };
    const uintptr_t addrToJump{ ((uintptr_t)myFunc - (uintptr_t)addrToHook) - jmpSyze };
        
    *(uintptr_t*) (addrToHook + 1) = addrToJump;

    VirtualProtect(addrToHook, len, currProtection, &currProtection);

    return savedByte;
}

void cleanFunction(BYTE* savedByte, BYTE* addrToClean, uintptr_t len)
{
        
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    // create a file to open a writtable console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Assault Cube Internal Trainer by Kalvin" << "\n";

    Entity* localPlayer{ EntityManager::GetLocalPlayerAddr() };

    // start DETOUR //

    BYTE*     savedByte  { nullptr };
    BYTE*     addrToHook { (BYTE*)(MemManager::modBaseAddr + 0x29D1F) };
    uintptr_t hookLen    { 5 };

    jmpBackAddr = (uintptr_t)addrToHook + hookLen;

    savedByte = toHook(addrToHook, hookLen, (BYTE*)GodMod_ASM);
    
    if (!savedByte)
        return -1;

    // end DETOUR // 
    
    localPlayer->m_health = 1337;

    // Hacking Loop
    while (!GetAsyncKeyState(VK_DELETE) & 1)
    {
        localPlayer->assaultRifleAmmo = 1337;
        localPlayer->magPistolAmmo = 1337;

        Aimbot::RunAimbot();
    }

    cleanFunction(savedByte, addrToHook, hookLen);

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