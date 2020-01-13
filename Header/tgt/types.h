#ifndef TGT_TYPES_H
#define TGT_TYPES_H

/*
 * This file is a derived work of the following file:
 */

/*
 * stdint.h - integer types for Win32
 * Copyright (C) 2003 ETC s.r.o.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the ETC s.r.o. nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2003.
 *
 */

/*
    This file defines the very practical C99 types et al.
    The most useful ones are:

    int8_t
    int16_t
    int32_t
    int64_t
    intptr_t

    uint8_t
    uint16_t
    uint32_t
    uint64_t
    uintptr_t
    uint

    size_t
    ulong

    TGT_UNUSED
*/

#include "tgt/config.h"

/**
 * This is needed for .dll or .so support respectively
 */

#ifdef TGT_BUILD_DLL
    #ifdef WIN32
        #define TGT_API __declspec(dllexport)
    #else //WIN32 - so it is UNIX -> I assume gcc
        #define TGT_API __attribute__ ((externally_visible))
    #endif //WIN32
#else //TGT_BUILD_DLL
    #ifdef WIN32
        #define TGT_API __declspec(dllimport)
    #else //WIN32 - so it is UNIX -> I assume gcc
        #define TGT_API __attribute__ ((externally_visible))
    #endif //WIN32
#endif //TGT_BUILD_DLL

/**
 * With this macro you can get rid of annoying "unused parameter" warnings
 */
#ifdef __GNUC__
    #define TGT_UNUSED __attribute__ ((unused))
#else
    /// empty macro for unsupported compilers
    #define TGT_UNUSED
#endif

#ifdef _MSC_VER
    #pragma warning( disable : 4100 )
#endif


// For size_t
#include <cstddef>

// Have not found a good place for this
#include <cstdlib>

/// ulong for 32 or 64 bit sizes. This depends on your arch and/or OS
typedef unsigned long ulong;

#if defined(__APPLE__) || (defined(WIN32) && defined(__GNUC__))
	/* unsigned int type */
	typedef unsigned int uint;
#endif

#ifdef _MSC_VER
    // For nasty microsoft compiler
    #define _USE_MATH_DEFINES

    #include <windows.h>
    #include <limits.h>

    /*
     * Integer Types
     */

    /* Exact-width integer types */

    #ifndef TGT_USE_SDL_WIN32
//    typedef CHAR     int8_t;
    #endif

    typedef SHORT    int16_t;
    typedef INT32    int32_t;
    typedef INT64    int64_t;
    typedef UCHAR   uint8_t;
    typedef WORD    uint16_t;
    typedef UINT32  uint32_t;
    typedef UINT64  uint64_t;

    /* unsigned int type */

    typedef unsigned int uint;

    /* Minimum-width integer types */

//    typedef CHAR     int_least8_t;
 /*   typedef SHORT    int_least16_t;
    typedef INT32    int_least32_t;
    typedef INT64    int_least64_t;
    typedef UCHAR   uint_least8_t;
    typedef WORD    uint_least16_t;
    typedef UINT32  uint_least32_t;
    typedef UINT64  uint_least64_t;*/

    /* Fastest minimum-width integer types */

   // typedef CHAR     int_fast8_t;
  //  typedef SHORT    int_fast16_t;
//    typedef INT32    int_fast32_t;
//    typedef INT64    int_fast64_t;
//    typedef UCHAR   uint_fast8_t;
////    typedef WORD    uint_fast16_t;
//    typedef UINT32  uint_fast32_t;
//    typedef UINT64  uint_fast64_t;
//
    /* Integer types capable of holding object pointers */

    typedef INT_PTR   intptr_t;
    typedef UINT_PTR uintptr_t;

    /* Greatest-width integer types */

    typedef INT64    intmax_t;
    typedef UINT64  uintmax_t;

 
#else // So it must be UNIX

    /*
        The ISO C99 standard specifies that in C++ implementations limit
        macros should only be defined if explicitly requested.
    */
    //FIXME: so this always defines the macros. the application should set
    // this define instead only if needed.
    #define __STDC_LIMIT_MACROS
    #include <stdint.h>
    // For uint - hope this works on all *NIX variants
    #include <sys/types.h>

#endif //WIN32

#ifdef WIN32
    #define TGT_PATH_SEPARATOR "\\"
#else
    #define TGT_PATH_SEPARATOR "/"
#endif


#endif //TGT_TYPES_H
