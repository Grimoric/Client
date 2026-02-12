#include "types.h"

/* External variables defined in MonochromeMonitor.cpp */
extern "C" int32_t data_829a68;   // Monitor status code
extern "C" uint8_t data_1417304;  // Initialization flag
extern "C" int32_t data_14182b0;  // Base address

/* External functions from MonochromeMonitor.cpp */
extern "C" void sub_5bc830(void);

/* sub_5bc7c0: UISystem_GetStatus */
extern "C" int32_t sub_5bc7c0(void) {
    return data_829a68;
}

/* sub_5bc6e0: UISystem_Initialize */
extern "C" void sub_5bc6e0(void) {
    if (data_1417304 == 0) {
        data_14182b0 = 0xb0000; // Physical address for MDA buffer
        sub_5bc830();           // Clear the monitor grid
        data_1417304 = 1;
    }
}

/* UISystem_EndLog Stub */
extern "C" void sub_5bc7e0(void) {
    return;
}