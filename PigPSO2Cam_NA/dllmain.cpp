#include <windows.h>
#include "dxhook.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);

        dllHandle = (HWND)hModule;
        installDXHooks();
      //  CreateThread(0, 0, (LPTHREAD_START_ROUTINE)installDXHooks, 0, 0, 0);
        break;
    }
    return TRUE;
}

