#ifndef TYPES_H
#define TYPES_H

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdio.h>

typedef uint8_t  uchar;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef STDCALL
#define STDCALL  __stdcall
#endif

#ifndef CDECL
#define CDECL    __cdecl
#endif

#ifndef FASTCALL
#define FASTCALL __fastcall
#endif

/* Simplified linkage macros to assist IntelliSense */
#ifdef __cplusplus
extern "C" {
#endif

	/* Common external globals used across modules */
	extern FILE* itow_alias;

#ifdef __cplusplus
}
#endif

#endif /* TYPES_H */