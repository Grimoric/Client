#include "types.h"
#include <string.h>

/* Global State Definitions (Owned by this module) */
extern "C" {
    int32_t data_829a68 = 0;       /* Monitor status code/state */
    uint8_t data_1417304 = 0;       /* Initialization flag */
    int32_t data_14182b0 = 0;       /* Base memory address (usually 0xB0000) */
    int32_t data_1417308 = 0;       /* Current cursor column (X) */
    int32_t data_141730c = 0;       /* Current cursor row (Y) */
    uint8_t data_14182b4 = 0;       /* Auto-scroll enabled flag */
    uint8_t data_1417310[4000] = { 0 }; /* Virtual text buffer (80x25 * 2 bytes) */
}

/* Forward declarations for internal routing */
extern "C" void sub_63bbd0(const char* format, ...); /* UOReport_Error */
extern "C" void sub_5bc800(void);                    /* Monitor_ResetCursor */
extern "C" void sub_5bc8a0(void);                    /* Monitor_ScrollBuffer */

/* sub_5bc800: Resets the monitor cursor to the top-left (0,0) */
extern "C" void sub_5bc800(void) {
    data_1417308 = 0;
    data_141730c = 0;
}

/* sub_5bc8a0: Scrolls the buffer up by one line and clears the bottom line */
extern "C" void sub_5bc8a0(void) {
    /* Move lines 1-24 to 0-23 (160 bytes per line) */
    memcpy(&data_1417310[0], &data_1417310[160], 3840);
    /* Clear the last line */
    memset(&data_1417310[3840], 0, 160);

    data_1417308 = 0;
    data_141730c = 24;
}

/* sub_5bc930: Hardware-level putchar. Handles line breaks and buffer overflows. */
extern "C" void sub_5bc930(char c) {
    /* Handle Newline (LF) */
    if (c == 0x0A) {
        data_1417308 = 0;
        data_141730c++;
        if (data_141730c == 25) {
            if (data_14182b4) sub_5bc8a0(); else sub_5bc800();
        }
        return;
    }

    /* Calculate 1D offset from 2D coordinates (X,Y) */
    int32_t offset = (data_141730c * 80 + data_1417308) << 1;

    if (offset >= 4000) {
        sub_63bbd0("MonochromeMonitor::putchar: offset >= 4000\n");
        sub_5bc800();
    }
    else {
        /* Write character and attribute (0x07 = Light Gray on Black) */
        data_1417310[offset] = (uint8_t)c;
        data_1417310[offset + 1] = 0x07;

        data_1417308++;
        if (data_1417308 == 80) {
            data_1417308 = 0;
            data_141730c++;
        }

        if (data_141730c == 25) {
            if (data_14182b4) sub_5bc8a0(); else sub_5bc800();
        }
    }
}

/* sub_5bc830: Clears the entire monitor with space characters */
extern "C" void sub_5bc830(void) {
    for (int i = 0; i < 2000; i++) sub_5bc930(0x20); /* 0x20 = Space */
    sub_5bc800();
}

/* sub_5bca70: Prints a null-terminated string to the monitor */
extern "C" void sub_5bca70(const char* text) {
    if (!text) return;
    while (*text) sub_5bc930(*text++);
}