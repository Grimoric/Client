#ifndef UO_CLIENT_H
#define UO_CLIENT_H

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

/* --- Global Data References --- */
extern "C" {
    // UOReport
    extern uint8_t  data_18a3370;
    extern uint8_t  data_18a3371;
    extern int32_t  data_18a336c;
    extern FILE* data_18a3b74;
    extern uint32_t data_82cfcc;
    extern char     data_18a3374[2048];
    extern uint8_t  data_18a3b73;

    // MemoryManager
    extern uint8_t  data_1414d50;
    extern uint32_t data_1414d5c;

    // MonochromeMonitor
    extern uint8_t  data_1417304;
    extern uint32_t data_14182b0;
    extern int32_t  data_829a68;
    extern uint8_t  data_14182b4;
    extern int32_t  data_1417308;
    extern int32_t  data_141730c;
    extern uint8_t  data_1417310[4000];

    // WinMain / Environment
    extern char     data_1419a50[256];
    extern int      data_141c0a8;
}

/* --- Function Prototypes --- */
extern "C" {
    // UOReport
    void sub_63b7d0();
    void sub_63ba80();
    void sub_63bbd0(const char* fmt, ...);
    void sub_63bc20(const char* fmt, ...);
    void sub_63bcc0(const char* fmt, ...);
    void sub_63bd10(const char* fmt, ...);
    void sub_63bd60(const char* prefix, const char* fmt, va_list args);
    void sub_63be20(const char* prefix, const char* message);

    // MemoryManager
    void sub_5b9a10();
    void sub_5b9a60();
    void sub_5b9b80();

    // ResourceSearch
    void sub_64a880();

    // MonochromeMonitor
    void sub_5bc6e0();
    void sub_5bc800();
    void sub_5bc830();
    void sub_5bc8a0();
    void sub_5bc930(char arg1);
    int32_t sub_5bc7c0();
    void sub_5bc7e0();
    void sub_5bca70(const char* text);
}

#endif