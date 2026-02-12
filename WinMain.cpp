#include <windows.h>
#include "UOReport.h"

/* Definition of the standard stream alias */
extern "C" FILE* itow_alias = stdout;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

    itow_alias = stdout;

    // UOReport_Start
    sub_63b7d0();

    // Register UOReport_Stop
    atexit(sub_63ba80);

    // First log entry
    sub_63bcc0("reached winmain!\n");

    return 0;
}