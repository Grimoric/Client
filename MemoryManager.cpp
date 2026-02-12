#include "UOClient.h"

extern "C" {
    uint8_t data_1414d50 = 0;
    uint32_t data_1414d5c = 0;

    void sub_63bd10(const char* message, ...);
    void sub_5b9b80(); // MemoryManager::report
}

/* 005b9b80: MemoryManager::report */
void sub_5b9b80() {
    sub_63bd10("MemoryManager::report:\n");
    sub_63bd10(" MemoryManager__OVERLOAD_GLOBAL_NEW_AND_DELETE not defined. nothing to report.\n");
}

/* 005b9a10: MemoryManager::start */
void sub_5b9a10() {
    sub_63bd10("MemoryManager::start\n");

    if (data_1414d50 != 0) {
        return;
    }

    data_1414d50 = 1;
    sub_63bd10("MemoryManager::started\n");
}

/* 005b9a60: MemoryManager::stop */
void sub_5b9a60() {
    sub_63bd10("MemoryManager::shutdown: stopping...\n");

    if (data_1414d50 == 0) {
        return;
    }

    // Generera slutrapport innan deallokering
    sub_5b9b80();

    data_1414d5c = 0;
    data_1414d50 = 0;

    sub_63bd10("MemoryManager::stopped.\n");
}