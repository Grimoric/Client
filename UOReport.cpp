#include "UOClient.h"

extern "C" {
    uint8_t  data_18a3370 = 0;
    uint8_t  data_18a3371 = 0;
    int32_t  data_18a336c = 0;
    FILE* data_18a3b74 = NULL;
    uint32_t data_82cfcc = 0;
    char     data_18a3374[2048] = { 0 };
    uint8_t  data_18a3b73 = 0;
}

void sub_63be20(const char* prefix, const char* message) {
    if (data_18a3b74 != NULL) {
        fprintf(data_18a3b74, "%s%s", prefix, message);
        fflush(data_18a3b74);
    }
    if (data_82cfcc & 0x8) {
        MessageBoxA(NULL, message, prefix, MB_OK);
    }
    if (data_82cfcc & 0x10) {
        if (sub_5bc7c0() == 2) {
            sub_5bca70(prefix);
            sub_5bca70(message);
            sub_5bc7e0();
        }
    }
}

void sub_63bd60(const char* prefix, const char* fmt, va_list args) {
    char message[2048];
    _vsnprintf(message, sizeof(message), fmt, args);
    sub_63be20(prefix, message);
}

void sub_63bd10(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    sub_63bd60("", fmt, args);
    va_end(args);
}

void sub_63bcc0(const char* fmt, ...) {
    va_list args;
    data_82cfcc = 0x15;
    va_start(args, fmt);
    sub_63bd60("UOReport::message: ", fmt, args);
    va_end(args);
}

void sub_63bc20(const char* fmt, ...) {
    va_list args;
    data_82cfcc = 0x15;
    va_start(args, fmt);
    sub_63bd60("UOReport::warning: ", fmt, args);
    va_end(args);
}

void sub_63bbd0(const char* fmt, ...) {
    va_list args;
    data_82cfcc = 0x1F;
    va_start(args, fmt);
    sub_63bd60("UOReport::error: ", fmt, args);
    va_end(args);
}

void sub_63ba80() {
    if (data_18a3b74 != NULL) {
        sub_63bcc0("closing report file\n");
        fclose(data_18a3b74);
        data_18a3b74 = NULL;
    }
}

void sub_63b7d0() {
    sub_5bc6e0();
    data_18a3b74 = fopen("uoreport.log", "a");
    if (data_18a3b74 == NULL) {
        sub_63bc20("could not open report file\n");
    }
    sub_63bcc0("opened report file\n");
}