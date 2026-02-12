#pragma once
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

	/* Logging Entry Points */
	void sub_63b7d0(void); // Startup
	void sub_63ba80(void); // Shutdown
	void sub_63bcc0(const char* format, ...); // Standard Message
	void sub_63bc20(const char* format, ...); // Generic Log
	void sub_63bbd0(const char* format, ...); // Error Reporter

	/* Internal Routing and Formatting */
	void sub_63bd60(const char* prefix, const char* format, va_list args);
	void sub_63be20(const char* prefix, const char* message);

#ifdef __cplusplus
}
#endif