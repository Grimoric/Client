#include "types.h"

// External reporting function from UOReport
extern "C" void sub_63bd10(const char* format, ...);

// Global state for MemoryManager (Win32 addresses)
extern "C" {
    uint8_t data_1414d50 = 0;   // IsStarted flag
    int32_t data_1414d5c = 0;   // Internal counter/state
}

/* sub_5b9b80: MemoryManager::report - Logs memory tracking status */
extern "C" void sub_5b9b80(void) {
    sub_63bd10("MemoryManager::report:\n");
    // In this build, global new/delete overloading is disabled.
    sub_63bd10(" MemoryManager__OVERLOAD_GLOBAL_NEW_AND_DELETE not defined. nothing to report.\n");
}

/* sub_5b9a10: MemoryManager::start */
extern "C" void sub_5b9a10(void) {
    sub_63bd10("MemoryManager::start\n");
    if (data_1414d50 == 0) {
        data_1414d50 = 1;
        sub_63bd10("MemoryManager::started\n");
    }
}

/* sub_5b9a60: MemoryManager::shutdown */
extern "C" void sub_5b9a60(void) {
    sub_63bd10("MemoryManager::shutdown: stopping...\n");
    if (data_1414d50 != 0) {
        sub_5b9b80(); // Call report before stopping
        data_1414d5c = 0;
        data_1414d50 = 0;
        sub_63bd10("MemoryManager::stopped.\n");
    }
}