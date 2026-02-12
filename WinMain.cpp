#include <windows.h>
#include <string.h>
#include "types.h"
#include "UOReport.h"

/* Definition of the global stdout proxy */
extern "C" FILE* itow_alias = NULL;

/* * Global Application Object / Linked List Head
 * Mapped to original binary behavior (ECX = this)
 */
struct GlobalList {
    void* head;

    void* __thiscall Constructor();
    void  __thiscall DestructorWrapper();
    void  __thiscall InternalCleanup();
    void* __thiscall ScalarDeletingDestructor(int flags);
};

/* External C-linkage symbols */
extern "C" {
    extern int32_t data_141c0a8;
    extern char    data_1419a50[256];

    /* The global instance pointer (0064ac68) */
    extern GlobalList* data_18a4b8c;

    /* Subsystem Prototypes */
    void sub_64a880(void); /* ResourceSearch_ProcessDiscovery */
    void sub_5b9a10(void); /* MemoryManager_Start */
    void sub_5b9a60(void); /* MemoryManager_Shutdown */
    void sub_64a7d0(void); /* exit handler */
}

/* Definition of the global instance pointer */
extern "C" GlobalList* data_18a4b8c = NULL;

/* * sub_5f8930: GlobalList Constructor
 * Observed at 005f8930. Initializes the head pointer to NULL.
 */
void* __thiscall GlobalList::Constructor() {
    this->head = NULL;
    return (void*)this;
}

/* * sub_5f8990: Internal Resource Cleanup
 * Observed at 005f8990. Traverses and deletes linked list nodes.
 */
void __thiscall GlobalList::InternalCleanup() {
    void* current = this->head;
    while (current != NULL) {
        /* Capture next pointer at offset +8 */
        void* next = *(void**)((char*)current + 8);
        operator delete(current);
        current = next;
    }
    this->head = NULL;
}

/* * sub_5f8960: Class destructor wrapper.
 * Observed at 005f8960.
 */
void __thiscall GlobalList::DestructorWrapper() {
    this->InternalCleanup();
}

/* * sub_64a830: Scalar deleting destructor.
 * Observed at 0064a830.
 */
void* __thiscall GlobalList::ScalarDeletingDestructor(int flags) {
    this->DestructorWrapper();
    if (flags & 0x1) {
        operator delete(this);
    }
    return (void*)this;
}

/* * sub_64a7d0: exit handler registered with atexit.
 * Observed at 0064a7d0.
 */
extern "C" void sub_64a7d0(void) {
    if (data_18a4b8c != NULL) {
        data_18a4b8c->ScalarDeletingDestructor(1);
        data_18a4b8c = NULL;
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    /* Set the standard output proxy */
    itow_alias = stdout;

    /* 1. Infrastructure (Logging) */
    sub_63b7d0();
    atexit(sub_63ba80);

    sub_63bcc0("reached winmain!\n");

    /* 2. Environment (Process Discovery) */
    data_141c0a8 = 0;
    memset(data_1419a50, 0, 0x100);
    sub_64a880();

    /* 3. Memory Subsystem */
    sub_5b9a10();
    atexit(sub_5b9a60);

    /* 4. Global Linked List Initialization (0064ac20) */
    /* Explicit casts added to satisfy C++ type safety */
    void* raw_mem = operator new(sizeof(GlobalList));
    if (raw_mem != NULL) {
        GlobalList* temp_obj = (GlobalList*)raw_mem;
        data_18a4b8c = (GlobalList*)temp_obj->Constructor();
    }
    else {
        data_18a4b8c = NULL;
    }

    atexit(sub_64a7d0);

    return 0;
}