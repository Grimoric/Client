#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include "UO_Client.h"

extern "C" {
    // Definition av globala variabler som används i WinMain
    char data_1419a50[256] = { 0 };
    void* data_18a4254 = NULL; // CreateToolhelp32Snapshot
    void* data_18a4250 = NULL; // Process32First
    void* data_18a424c = NULL; // Process32Next
}

// Funktionspekare för att matcha disassemblyns dynamiska laddning
typedef HANDLE(WINAPI* P_CT32S)(DWORD, DWORD);
typedef BOOL(WINAPI* P_P32F)(HANDLE, LPPROCESSENTRY32);
typedef BOOL(WINAPI* P_P32N)(HANDLE, LPPROCESSENTRY32);

void sub_64a880() {
    // Hämtar version för OS-kontroll (Disassembly 0064a88c)
#pragma warning(push)
#pragma warning(disable : 4996)
    DWORD dwVersion = GetVersion();
#pragma warning(pop)

    // Dynamisk laddning av kernel32 för att hämta Toolhelp-funktioner
    HMODULE hKernel = LoadLibraryA("kernel32.dll");
    if (hKernel == NULL) return;

    data_18a4254 = (void*)GetProcAddress(hKernel, "CreateToolhelp32Snapshot");
    data_18a4250 = (void*)GetProcAddress(hKernel, "Process32First");
    data_18a424c = (void*)GetProcAddress(hKernel, "Process32Next");

    if (!data_18a4254 || !data_18a4250 || !data_18a424c) {
        FreeLibrary(hKernel);
        return;
    }

    FreeLibrary(hKernel);

    DWORD myPid = GetCurrentProcessId();
    DWORD parentPid = 0;

    // Skapa snapshot av processer (Disassembly 0064a95d)
    HANDLE hSnapshot = ((P_CT32S)data_18a4254)(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 pe;
    memset(&pe, 0, sizeof(pe));
    pe.dwSize = sizeof(pe);

    // Iterera för att hitta nuvarande process och dess förälder
    if (((P_P32F)data_18a4250)(hSnapshot, &pe)) {
        do {
            if (pe.th32ProcessID == myPid) {
                parentPid = pe.th32ParentProcessID;
                break;
            }
            pe.dwSize = sizeof(pe);
        } while (((P_P32N)data_18a424c)(hSnapshot, &pe));
    }

    // Om förälder hittades, hämta dess filnamn (Disassembly 0064aa1e)
    if (parentPid != 0) {
        pe.dwSize = sizeof(pe);
        if (((P_P32F)data_18a4250)(hSnapshot, &pe)) {
            do {
                if (pe.th32ProcessID == parentPid) {
                    char* lastSlash = strrchr(pe.szExeFile, '\\');
                    const char* fileName = (lastSlash != NULL) ? lastSlash + 1 : pe.szExeFile;

                    // Kopiera till global buffert (Disassembly 0064aa63)
                    strncpy(data_1419a50, fileName, 0xC0);
                    break;
                }
                pe.dwSize = sizeof(pe);
            } while (((P_P32N)data_18a424c)(hSnapshot, &pe));
        }
    }

    CloseHandle(hSnapshot);
}