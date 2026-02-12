#include "UO_Client.h"

extern "C" {
    int  data_141c0a8 = 0;
}

// Explicit ANSI entry point to match binary linkage
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    sub_63b7d0();
    atexit(sub_63ba80);
    sub_63bcc0("reached winmain!\n");

    data_141c0a8 = 0;
    memset(data_1419a50, 0, 0x100);

    sub_64a880();
    sub_5b9a10();
    atexit(sub_5b9a60);

    return 0;
}