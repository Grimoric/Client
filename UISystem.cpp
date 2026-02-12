#include "types.h"

/* External state references from MonochromeMonitor.cpp */
extern "C" {
    extern int32_t data_829a68;   /* Monitor status */
    extern uint8_t data_1417304;  /* Init flag */
    extern int32_t data_14182b0;  /* Base address */

    void sub_5bc830(void);        /* Monitor_Clear */
}

/* sub_5bc7c0: UISystem_GetStatus - Returns the current monitor state */
extern "C" int32_t sub_5bc7c0(void) {
    return data_829a68;
}

/* sub_5bc6e0: UISystem_Initialize - Prepares hardware for logging */
extern "C" void sub_5bc6e0(void) {
    if (data_1417304 == 0) {
        /* Define MDA video buffer address */
        data_14182b0 = 0xb0000;

        /* Wipe display for fresh log session */
        sub_5bc830();
        data_1417304 = 1;

        /* Set system status to 'Ready' (2) */
        data_829a68 = 2;
    }
}

/* sub_5bc7e0: UISystem_EndLogEntry - Placeholder for frame-end operations */
extern "C" void sub_5bc7e0(void) {
    /* No logic observed in this build */
    return;
}