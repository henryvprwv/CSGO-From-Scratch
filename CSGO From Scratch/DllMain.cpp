#include <Windows.h>

DWORD WINAPI StartupThread(HINSTANCE hinstDLL)
{
    while (!(GetAsyncKeyState(VK_END)))
        Sleep(200);

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