#pragma once
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

	/* Standard Logging */
	void sub_63b7d0(void);
	void sub_63ba80(void);
	void sub_63bcc0(const char* format, ...);
	void sub_63bc20(const char* format, ...);
	void sub_63bbd0(const char* format, ...);

	/* Raw Logging (Required by MemoryManager) */
	void sub_63bd10(const char* format, ...);

	/* Internal Routing */
	void sub_63bd60(const char* prefix, const char* format, va_list args);
	void sub_63be20(const char* prefix, const char* message);

#ifdef __cplusplus
}
#endif