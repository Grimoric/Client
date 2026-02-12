#include "types.h"
#include "UOReport.h"

extern "C" {
    uint8_t data_1414d50 = 0;   /* IsStarted flag */
    int32_t data_1414d5c = 0;   /* Internal state/counter */
}

/* sub_5b9b80: MemoryManager::report - Logs allocation status */
extern "C" void sub_5b9b80(void) {
    sub_63bd10("MemoryManager::report:\n");
    /* Note: Tracking is disabled in this build (OVERLOAD_GLOBAL_NEW_AND_DELETE undefined) */
    sub_63bd10(" MemoryManager__OVERLOAD_GLOBAL_NEW_AND_DELETE not defined. nothing to report.\n");
}

/* sub_5b9a10: MemoryManager::start - Initializes memory tracking subsystem */
extern "C" void sub_5b9a10(void) {
    sub_63bd10("MemoryManager::start\n");
    if (data_1414d50 == 0) {
        data_1414d50 = 1;
        sub_63bd10("MemoryManager::started\n");
    }
}

/* sub_5b9a60: MemoryManager::shutdown - Finalizes tracking and reports leaks */
extern "C" void sub_5b9a60(void) {
    sub_63bd10("MemoryManager::shutdown: stopping...\n");
    if (data_1414d50 != 0) {
        sub_5b9b80(); /* Output final report before exit */
        data_1414d5c = 0;
        data_1414d50 = 0;
        sub_63bd10("MemoryManager::stopped.\n");
    }
}