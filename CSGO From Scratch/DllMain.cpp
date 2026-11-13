#include <Windows.h>
#include <iostream>

#include <Core/Cheat Manager/Cheat Manager.h>

DWORD WINAPI StartupThread(HINSTANCE hinstDLL)
{
    if (!GetCheatManager()->OnInit())
        std::cout << "Init Failed!\n";
    else
        std::cout << "Init Success!\n";

    while (!(GetAsyncKeyState(VK_END) & 0x8000))
        Sleep(200);

    GetCheatManager()->OnShutdown();

    FreeLibraryAndExitThread(hinstDLL, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,  DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);

        const auto Thread = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartupThread), hinstDLL, NULL, nullptr);

        if (Thread)
            CloseHandle(Thread);
    }

    return TRUE;
}