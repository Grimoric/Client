#include <windows.h>
#include <string.h>
#include "types.h"
#include "UOReport.h"

// All extern declarations at global scope
extern "C" {
    // These variables live in ResourceSearch.cpp, we only reference them here
    extern int32_t data_141c0a8;
    extern char data_1419a50[256];

    // This variable lives in WinMain.cpp (defined below) or as a proxy
    extern FILE* itow_alias;

    // Subsystem functions
    void sub_64a880(void);
    void sub_5b9a10(void);
    void sub_5b9a60(void);
}

// Definition of the alias (this is the owner of the variable)
extern "C" FILE* itow_alias = stdout;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

    itow_alias = stdout;

    // Initialize Reporting
    sub_63b7d0();
    atexit(sub_63ba80);

    sub_63bcc0("reached winmain!\n");

    // Reset search flags and clear buffer
    data_141c0a8 = 0;
    memset(data_1419a50, 0, 0x100);

    // Run resource search
    sub_64a880();

    // Start Memory Management
    sub_5b9a10();
    atexit(sub_5b9a60);

    return 0;
}