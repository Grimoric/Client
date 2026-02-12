#include "types.h"
#include <string.h>

/* Global Definitions (The only place these are defined) */
extern "C" int32_t data_829a68 = 0;
extern "C" uint8_t data_1417304 = 0;
extern "C" int32_t data_14182b0 = 0;
extern "C" int32_t data_1417308 = 0; // Column
extern "C" int32_t data_141730c = 0; // Row
extern "C" uint8_t data_14182b4 = 0; // Scroll flag
extern "C" uint8_t data_1417310[4000] = { 0 }; // Buffer

/* Forward declarations */
extern "C" void sub_63bbd0(const char* format, ...);
extern "C" void sub_5bc800(void);
extern "C" void sub_5bc8a0(void);

/* Monitor logic implementation */
extern "C" void sub_5bc800(void) {
    data_1417308 = 0;
    data_141730c = 0;
}

extern "C" void sub_5bc8a0(void) {
    memcpy(&data_1417310[0], &data_1417310[160], 3840);
    memset(&data_1417310[3840], 0, 160);
    data_1417308 = 0;
    data_141730c = 24;
}

extern "C" void sub_5bc930(char arg1) {
    if (arg1 == 0x0A) {
        data_1417308 = 0;
        data_141730c++;
        if (data_141730c == 25) {
            if (data_14182b4) sub_5bc8a0(); else sub_5bc800();
        }
        return;
    }

    int32_t offset = (data_141730c * 80 + data_1417308) << 1;
    if (offset >= 4000) {
        sub_63bbd0("MonochromeMonitor::putchar: offset >= 4000\n");
        sub_5bc800();
    }
    else {
        data_1417310[offset] = (uint8_t)arg1;
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

extern "C" void sub_5bc830(void) {
    for (int i = 0; i < 2000; i++) sub_5bc930(0x20);
    sub_5bc800();
}

extern "C" void sub_5bca70(const char* text) {
    if (!text) return;
    while (*text) sub_5bc930(*text++);
}