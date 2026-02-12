#include "UO_Client.h"

extern "C" {
    // 018a4b8c: Central global object pointer
    void* data_18a4b8c = nullptr;
}

/* 005f8990: Core cleanup logic for the manager's linked list */
void __fastcall sub_5f8990(void* pThis, void* dummyEDX) {
    if (pThis == nullptr) return;

    // The manager object holds a pointer to the first node at offset +0x0
    void** ppHead = (void**)pThis;
    void* pCurrent = *ppHead;

    // Traverse and delete all nodes in the linked list
    while (pCurrent != nullptr) {
        // Offset +0x8 contains the pointer to the next node
        void* pNext = *(void**)((uintptr_t)pCurrent + 0x8);

        // Free the memory of the current node
        operator delete(pCurrent);

        // Move to the next node
        pCurrent = pNext;
    }

    // Reset the head pointer to NULL after cleanup
    *ppHead = nullptr;
}

/* 005f8930: Basic Constructor
   Emulates __thiscall using __fastcall (ECX = pThis) */
void* __fastcall sub_5f8930(void* pThis, void* dummyEDX) {
    // Initialize the linked list head pointer to NULL
    if (pThis != nullptr) {
        *(uint32_t*)pThis = 0;
    }
    return pThis;
}

/* 005f8960: Member Destructor
   Called by the scalar deleting destructor to clean up resources */
void __fastcall sub_5f8960(void* pThis, void* dummyEDX) {
    if (pThis != nullptr) {
        // Delegate actual linked list cleanup to sub_5f8990
        sub_5f8990(pThis, nullptr);
    }
}

/* 0064a830: Scalar Deleting Destructor
   Emulates __thiscall. flag & 1: also calls operator delete on the manager itself */
void* __fastcall sub_64a830(void* pThis, void* dummyEDX, uint8_t flag) {
    if (pThis != nullptr) {
        // 1. Call the member destructor (cleans up the list)
        sub_5f8960(pThis, nullptr);

        // 2. Conditionally free the memory allocated for the manager object
        if (flag & 1) {
            operator delete(pThis);
        }
    }
    return pThis;
}

/* 0064a7d0: Cleanup handler registered with atexit */
void sub_64a7d0() {
    if (data_18a4b8c != nullptr) {
        // Trigger full destruction and memory release
        sub_64a830(data_18a4b8c, nullptr, 1);
        data_18a4b8c = nullptr;
    }
}