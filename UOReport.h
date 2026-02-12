#pragma once
#include "types.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

	/* Standard Logging Entry Points */
	void sub_63b7d0(void); /* UOReport_Start */
	void sub_63ba80(void); /* UOReport_Stop */
	void sub_63bcc0(const char* format, ...); /* UOReport_Message */
	void sub_63bc20(const char* format, ...); /* UOReport_Status */
	void sub_63bbd0(const char* format, ...); /* UOReport_Error */

	/* Raw Logging (Required by MemoryManager) */
	void sub_63bd10(const char* format, ...);

	/* Internal Dispatchers */
	void sub_63bd60(const char* prefix, const char* format, va_list args);
	void sub_63be20(const char* prefix, const char* message);

#ifdef __cplusplus
}
#endif