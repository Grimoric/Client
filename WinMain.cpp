#include "UOClient.h"

extern "C" {
    int data_141c0a8 = 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 0064abcc: Initialize logging subsystem
    sub_63b7d0();
    atexit(sub_63ba80);

    // 0064abde: Trace entry point
    sub_63bcc0("reached winmain!\n");

    // 0064abeb: Clear global application state
    data_141c0a8 = 0;
    memset(data_1419a50, 0, 0x100);

    // 0064ac09: Identify process and resource path
    sub_64a880();

    // 0064ac0e: Start global memory manager
    sub_5b9a10();
    atexit(sub_5b9a60);

    // 0064ac20: Allocate central manager object (4 bytes)
    void* pObj = operator new(4);
    if (pObj != nullptr) {
        // Initialize object using constructor emulation
        sub_5f8930(pObj, nullptr);
        data_18a4b8c = pObj;
    }

    // 0064ac6e: Register global manager for automatic cleanup
    atexit(sub_64a7d0);

    return 0;
}
