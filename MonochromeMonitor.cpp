#include "UOClient.h"
#include <string.h>

extern "C" {
    uint8_t  data_1417304 = 0;
    uint32_t data_14182b0 = 0;
    int32_t  data_829a68 = 0;
    uint8_t  data_14182b4 = 0;
    int32_t  data_1417308 = 0;
    int32_t  data_141730c = 0;
    uint8_t  data_1417310[4000] = { 0 };
}

/* 005bc800: Reset cursor to top-left */
void sub_5bc800() {
    data_1417308 = 0;
    data_141730c = 0;
}

/* 005bc8a0: Scroll screen content up by one row */
void sub_5bc8a0() {
    // Move rows 1-24 to 0-23
    // Offset for row 1: 80 * 1 * 2 = 160 (0xA0)
    // 0x1417310 + 0xA0 = 0x14173B0
    memcpy(&data_1417310[0], &data_1417310[160], 3950);

    // Clear the last row (Row 24)
    // 0x1417310 + (24 * 80 * 2) = 0x1417310 + 3840 (0xF00) = 0x1418210
    memset(&data_1417310[3840], 0, 160);

    data_1417308 = 0;
    data_141730c = 24;
}

/* 005bc930: Internal putchar with wrap/scroll logic */
void sub_5bc930(char arg1) {
    uint8_t c = (uint8_t)arg1;

    if (c == 0x0A) {
        data_1417308 = 0;
        data_141730c++;
        if (data_141730c == 25) {
            if (data_14182b4) sub_5bc8a0();
            else sub_5bc800();
        }
        return;
    }

    int32_t offset = ((data_141730c * 80) + data_1417308) * 2;

    if (offset >= 4000) {
        sub_63bbd0("MonochromeMonitor::putchar: offset >= SCREEN_WIDTH * SCREEN_HEIGHT * 2\n");
        sub_5bc800();
    }
    else {
        data_1417310[offset] = c;
        data_1417310[offset + 1] = 0x07;

        data_1417308++;
        if (data_1417308 == 80) {
            data_1417308 = 0;
            data_141730c++;
        }
    }

    if (data_141730c == 25) {
        if (data_14182b4) sub_5bc8a0();
        else sub_5bc800();
    }
}

void sub_5bc830() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            sub_5bc930(0x20);
        }
    }
    sub_5bc800();
}

void sub_5bc6e0() {
    if (data_1417304 == 0) {
        data_14182b0 = 0xb0000;
        sub_5bc830();
        data_1417304 = 1;
    }
}

int32_t sub_5bc7c0() { return data_829a68; }
void sub_5bc7e0() {}
void sub_5bca70(const char* arg1) {
    if (!arg1) return;
    for (const char* p = arg1; *p; p++) sub_5bc930(*p);
}