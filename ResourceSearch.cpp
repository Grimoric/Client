#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include "UOClient.h"

extern "C" {
    // 01419a50: Global buffer for process name
    char data_1419a50[256] = { 0 };

    // Function pointers for Toolhelp32 (resolved dynamically)
    void* data_18a4254 = nullptr; // CreateToolhelp32Snapshot
    void* data_18a4250 = nullptr; // Process32First
    void* data_18a424c = nullptr; // Process32Next
}

// Function pointer types to match disassembly calls
typedef HANDLE(WINAPI* P_CT32S)(DWORD, DWORD);
typedef BOOL(WINAPI* P_P32F)(HANDLE, LPPROCESSENTRY32);
typedef BOOL(WINAPI* P_P32N)(HANDLE, LPPROCESSENTRY32);

/* 0064a880: Search for parent process name */
void sub_64a880() {
    // 0064a88c: Get OS Version
    GetVersion();

    // 0064a895: Hardcoded branch to 0x64a8c0
    // Observation: The block at 0064a89b is unreachable in this binary.

    // 0064a8c0: Load kernel32.dll
    HMODULE hKernel = LoadLibraryA("kernel32.dll");
    if (hKernel == nullptr) {
        return;
    }

    // 0064a8d9: Resolve Toolhelp32 symbols
    data_18a4254 = (void*)GetProcAddress(hKernel, "CreateToolhelp32Snapshot");
    if (data_18a4254 == nullptr) {
        FreeLibrary(hKernel);
        return;
    }

    data_18a4250 = (void*)GetProcAddress(hKernel, "Process32First");
    if (data_18a4250 == nullptr) {
        FreeLibrary(hKernel);
        return;
    }

    data_18a424c = (void*)GetProcAddress(hKernel, "Process32Next");
    if (data_18a424c == nullptr) {
        FreeLibrary(hKernel);
        return;
    }

    // 0064a93f: Free library handle after resolving addresses
    FreeLibrary(hKernel);

    // 0064a949: Get current process context
    DWORD myPid = GetCurrentProcessId();
    DWORD parentPid = 0;

    // 0064a95d: Create process snapshot (0xF = TH32CS_SNAPALL)
    HANDLE hSnapshot = ((P_CT32S)data_18a4254)(0xF, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return;
    }

    // 0064a966: Initialize PROCESSENTRY32 structure
    PROCESSENTRY32 pe;
    memset(&pe, 0, sizeof(pe));
    pe.dwSize = sizeof(pe); // 0x128

    // 0064a991: First pass - find current process to identify parent PID
    if (((P_P32F)data_18a4250)(hSnapshot, &pe)) {
        do {
            if (pe.th32ProcessID == myPid) {
                parentPid = pe.th32ParentProcessID;
                break;
            }
        } while (((P_P32N)data_18a424c)(hSnapshot, &pe));
    }

    // 0064a9d5: Second pass - find the parent process name
    if (parentPid != 0) {
        pe.dwSize = sizeof(pe);
        if (((P_P32F)data_18a4250)(hSnapshot, &pe)) {
            do {
                if (pe.th32ProcessID == parentPid) {
                    // 0064aa15: Extract filename from path using last backslash
                    char* lastSlash = strrchr(pe.szExeFile, 0x5C); // '\\'
                    const char* fileName = (lastSlash != nullptr) ? lastSlash + 1 : pe.szExeFile;

                    // 0064aa5e: Copy result to global buffer
                    strncpy(data_1419a50, fileName, 0xC0);
                    break;
                }
            } while (((P_P32N)data_18a424c)(hSnapshot, &pe));
        }
    }

    // 0064aa89: Cleanup snapshot handle
    CloseHandle(hSnapshot);
}