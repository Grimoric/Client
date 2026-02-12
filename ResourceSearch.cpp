#include "types.h"
#include "UOReport.h"
#include <windows.h>
#include <string.h>

/* Constants and structures defined locally to ensure ANSI compatibility
   regardless of project SDK settings. */
#define TH32CS_SNAPPROCESS 0x00000002

struct struct_PROCESSENTRY32A {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID;
    ULONG_PTR th32DefaultHeapID;
    DWORD th32ModuleID;
    DWORD cntThreads;
    DWORD th32ParentProcessID;
    LONG  pcPriClassBase;
    DWORD dwFlags;
    CHAR  szExeFile[MAX_PATH];
};

typedef HANDLE(WINAPI* FN_CreateToolhelp32Snapshot)(DWORD, DWORD);
typedef BOOL(WINAPI* FN_Process32FirstA)(HANDLE, struct_PROCESSENTRY32A*);
typedef BOOL(WINAPI* FN_Process32NextA)(HANDLE, struct_PROCESSENTRY32A*);

extern "C" {
    int32_t data_141c0a8 = 0;
    char data_1419a50[256] = { 0 };

    FN_CreateToolhelp32Snapshot data_18a4254 = NULL;
    FN_Process32FirstA           data_18a4250 = NULL;
    FN_Process32NextA            data_18a424c = NULL;
}

#pragma warning(disable : 4996) /* Disable GetVersion deprecation warning */

/* sub_64a880: Enumerates system processes to identify the current executable name. */
extern "C" void sub_64a880(void) {
    DWORD dwVersion = GetVersion();

    /* OS Compatibility check (matching binary 0064a89b) */
    if ((dwVersion & 0xFF) <= 4) return;

    /* Resolve Toolhelp32 functions from kernel32.dll at runtime */
    HMODULE hKernel = GetModuleHandleA("kernel32.dll");
    if (hKernel) {
        data_18a4254 = (FN_CreateToolhelp32Snapshot)GetProcAddress(hKernel, "CreateToolhelp32Snapshot");
        data_18a4250 = (FN_Process32FirstA)GetProcAddress(hKernel, "Process32First");
        data_18a424c = (FN_Process32NextA)GetProcAddress(hKernel, "Process32Next");
    }

    if (!data_18a4254 || !data_18a4250 || !data_18a424c) return;

    DWORD myPid = GetCurrentProcessId();
    HANDLE hSnapshot = data_18a4254(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot != INVALID_HANDLE_VALUE) {
        struct_PROCESSENTRY32A pe32;
        memset(&pe32, 0, sizeof(pe32));
        pe32.dwSize = sizeof(struct_PROCESSENTRY32A);

        if (data_18a4250(hSnapshot, &pe32)) {
            do {
                if (pe32.th32ProcessID == myPid) {
                    /* Strip path to isolate the filename */
                    char* fileName = strrchr(pe32.szExeFile, '\\');
                    if (fileName) {
                        fileName++;
                    }
                    else {
                        fileName = pe32.szExeFile;
                    }

                    /* Copy to global BSS buffer (max 192 bytes per 0xC0 limit) */
                    strncpy(data_1419a50, fileName, 0xC0);

                    /* RE-ENGINEERING LOGGING: Verification for reconstructed build */
                    sub_63bcc0("ResourceSearch: Identified process name as '%s'\n", data_1419a50);

                    break;
                }
            } while (data_18a424c(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }
}