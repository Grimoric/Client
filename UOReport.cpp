#include "UOReport.h"
#include <stdio.h>

extern "C" {
    void sub_5bc6e0(void);
    int32_t sub_5bc7c0(void);
    void sub_5bca70(const char* text);
    void sub_5bc7e0(void);
}

uint8_t data_18a3370 = 0;
uint8_t data_18a3371 = 0;
int32_t data_82cfcc = 0;
char    data_18a3374[2048];
FILE* data_18a3b74 = NULL;

void sub_63b7d0(void) {
    if (data_18a3370 == 0) {
        data_18a3370 = 1;
        data_18a3b74 = fopen("UOReport0.log", "wt");
    }
    sub_5bc6e0();
}

void sub_63ba80(void) {
    if (data_18a3370 == 0 || data_18a3371 != 0) return;
    if (data_18a3b74) {
        fclose(data_18a3b74);
        data_18a3b74 = NULL;
    }
    data_18a3371 = 1;
}

void sub_63be20(const char* prefix, const char* message) {
    if (!data_18a3370) sub_63b7d0();
    if ((data_82cfcc & 0x02) && itow_alias) {
        fprintf(itow_alias, "%s%s", prefix, message);
    }
    if ((data_82cfcc & 0x04) && data_18a3b74) {
        fprintf(data_18a3b74, "%s%s", prefix, message);
        fflush(data_18a3b74);
    }
    if ((data_82cfcc & 0x10) && sub_5bc7c0() == 2) {
        sub_5bca70(prefix);
        sub_5bca70(message);
        sub_5bc7e0();
    }
}

void sub_63bd60(const char* prefix, const char* format, va_list args) {
    if (!prefix && !format) return;
    data_18a3374[0] = '\0';
    if (format) _vsnprintf(data_18a3374, 2047, format, args);
    sub_63be20(prefix, data_18a3374);
}

extern "C" void sub_63bd10(const char* format, ...) {
    data_82cfcc = 0x15;
    va_list args; va_start(args, format);
    sub_63bd60("", format, args);
    va_end(args);
}

extern "C" void sub_63bcc0(const char* format, ...) {
    data_82cfcc = 0x15;
    va_list args; va_start(args, format);
    sub_63bd60("UOReport::message: ", format, args);
    va_end(args);
}

extern "C" void sub_63bbd0(const char* format, ...) {
    data_82cfcc = 0x1F;
    va_list args; va_start(args, format);
    sub_63bd60("UOReport::error: ", format, args);
    va_end(args);
}