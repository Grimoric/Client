#include "UOReport.h"

/* External UISystem dependencies */
extern "C" void sub_5bc6e0(void);    // UISystem_Init
extern "C" int32_t sub_5bc7c0(void); // UISystem_Status
extern "C" void sub_5bca70(const char* text); // UISystem_Puts
extern "C" void sub_5bc7e0(void);    // UISystem_EndLog

/* Global State Variables */
uint8_t data_18a3370 = 0;   // System Started Flag
uint8_t data_18a3371 = 0;   // System Stopped Flag
uint8_t data_18a3372 = 0;   // Errata Logging Active Flag
int32_t data_18a336c = 0;   // Log File Instance Index
int32_t data_82cfcc = 0;   // Output Bitmask
char    data_18a3374[2048]; // String Formatting Buffer
FILE* data_18a3b74 = NULL;  // Active Log File Handle
extern "C" FILE* itow_alias; // Global pointer to stdout/stderr

/* UOReport::start - Initializes logging and handles file creation */
void sub_63b7d0(void) {
    char filename[256];
    const char* mode = "wt";

    if (data_18a3371 != 0) {
        data_18a3372 = 1;
        sprintf(filename, "UOErrata%d.log", data_18a336c);
        sub_63bc20("UOReport::start: already started & stopped! look in file '%s' for further information.\n", filename);
        data_18a3b74 = fopen(filename, mode);
    }
    else if (data_18a3370 == 0) {
        data_18a3370 = 1;
        sprintf(filename, "UOReport%d.log", data_18a336c);
        data_18a3b74 = fopen(filename, mode);

        if (data_18a3b74) {
            sub_63bcc0("UOReport: created file '%s' for writing.\n", filename);
        }
        else {
            sub_63bc20("UOReport: cannot open file '%s' for writing.\n", filename);
        }

        sub_63bcc0("UOReport: starting up...\n");

        HANDLE hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, "UOReport::startup");
        if (hMutex != NULL) {
            data_18a336c++;
            CloseHandle(hMutex);
        }
        else {
            hMutex = CreateMutexA(NULL, FALSE, "UOReport::startup");
            if (hMutex && GetLastError() == ERROR_ALREADY_EXISTS) {
                data_18a336c++;
            }
        }
    }
    sub_5bc6e0(); // Init UISystem/Monitor
    sub_63bcc0("UOReport: started.\n");
}

/* UOReport::stop - Cleanup and closure of file handles */
void sub_63ba80(void) {
    if (data_18a3370 == 0 || data_18a3371 != 0) return;

    sub_63bcc0("UOReport: stopping...\n");
    if (data_18a3b74) {
        fclose(data_18a3b74);
        data_18a3b74 = NULL;
    }
    data_18a3371 = 1;
}

/* UOReport_Router - Routes messages to file, console, or monitor */
void sub_63be20(const char* arg1, const char* arg2) {
    if (!data_18a3370) sub_63b7d0();

    if ((data_82cfcc & 0x28) == 0x28) MessageBoxA(NULL, arg2, arg1, MB_OK);
    if ((data_82cfcc & 0x02) && itow_alias) fprintf(itow_alias, "%s%s", arg1, arg2);
    if ((data_82cfcc & 0x04) && data_18a3b74) {
        fprintf(data_18a3b74, "%s%s", arg1, arg2);
        fflush(data_18a3b74);
    }
    if ((data_82cfcc & 0x10) && sub_5bc7c0() == 2) {
        sub_5bca70(arg1);
        sub_5bca70(arg2);
        sub_5bc7e0();
    }
}

/* Internal Formatter using vsnprintf */
void sub_63bd60(const char* prefix, const char* format, va_list args) {
    if (!prefix && !format) return;
    data_18a3374[0] = '\0';
    if (format) _vsnprintf(data_18a3374, 2047, format, args);
    sub_63be20(prefix, data_18a3374);
}

void sub_63bcc0(const char* format, ...) {
    data_82cfcc = 0x15;
    va_list args; va_start(args, format);
    sub_63bd60("UOReport::message: ", format, args);
    va_end(args);
}

/* sub_63bd10: Raw log function (No hardcoded prefix) */
void sub_63bd10(const char* format, ...) {
    data_82cfcc = 0x15;
    va_list args;
    va_start(args, format);
    // data_7a8fa8 was identified as empty string ""
    sub_63bd60("", format, args);
    va_end(args);
}

void sub_63bbd0(const char* format, ...) {
    data_82cfcc = 0x1F;
    va_list args; va_start(args, format);
    sub_63bd60("UOReport::error: ", format, args);
    va_end(args);
}

void sub_63bc20(const char* format, ...) {
    va_list args; va_start(args, format);
    sub_63bd60("UOReport: ", format, args);
    va_end(args);
}