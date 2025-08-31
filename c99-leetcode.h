// c99-leetcode.h - v0.1 - tiny stb-style single-header "Hello, World!" library
// Public Domain or MIT, your choice, see end of file.
//
// Minimal example of the stb single-header pattern.
// No allocations, no dependencies beyond the C standard library.
//
// DOCUMENTATION
//
//   Overview:
//     A trivial API that returns "Hello, World!" either as a const string
//     or by writing it into a caller-provided buffer.
//
//   Defines that control this header:
//     C99_LEETCODE_STATIC
//         Define before including the *implementation* to make function
//         definitions 'static' so each including .c/.cpp gets its own copy.
//     C99_LEETCODE_IMPLEMENTATION
//         Define in exactly one .c/.cpp before including this header to
//         compile the implementation.
//     C99_LEETCODE_NO_STDIO
//         Omit stdio-based sample helpers if you add any that use stdio.
//
//   Build:
//     In one source file:
//         #define C99_LEETCODE_IMPLEMENTATION
//         #include "c99-leetcode.h"
//     In all other files:
//         #include "c99-leetcode.h"
//
//   API:
//     C99_LEETCODE_PUBLIC_DECL const char* c99lc_helloworld(void);
//       Returns a pointer to a constant, null-terminated "Hello, World!".
//
//     C99_LEETCODE_PUBLIC_DECL int c99lc_helloworld_into(char* out, size_t out_cap);
//       Writes "Hello, World!" into 'out' with null-termination.
//       Returns the number of bytes written excluding the terminator.
//       Writes nothing and returns 0 if out is NULL or out_cap == 0.
//
// VERSION HISTORY
//   0.1  Initial release.
//
// CONTRIBUTORS
//   %_YOU_%.
//
// LICENSE
//   See end of file for license information.

#ifndef C99_LEETCODE_H_INCLUDE
#define C99_LEETCODE_H_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

// Public declaration macro: resolves to extern or extern "C" for C++.
// Users can override by defining c99lc_PUBLIC_DECL before this include.
#ifndef C99_LEETCODE_PUBLIC_DECL
#  ifdef C99_LEETCODE_STATIC
#    define C99_LEETCODE_PUBLIC_DECL static
#  else
#    ifdef __cplusplus
#      define C99_LEETCODE_PUBLIC_DECL extern "C"
#    else
#      define C99_LEETCODE_PUBLIC_DECL extern
#    endif
#  endif
#endif

// Optional configuration hooks for future allocation needs.
// Not used by this template, but provided to match stb guidance.
#ifndef C99_LEETCODE_NO_ALLOC
#  include <stddef.h> // size_t for allocator signatures if you use them later
#  ifndef C99_LEETCODE_MALLOC
#    include <stdlib.h>
#    define C99_LEETCODE_MALLOC(ctx, size)        ((void)(ctx), malloc(size))
#    define C99_LEETCODE_FREE(ctx, ptr)           ((void)(ctx), free(ptr))
#    define C99_LEETCODE_REALLOC(ctx, ptr, size)  ((void)(ctx), realloc(ptr, size))
#  endif
#endif

// Public API
C99_LEETCODE_PUBLIC_DECL const char* c99lc_helloworld(void);
C99_LEETCODE_PUBLIC_DECL int         c99lc_helloworld_into(char* out, size_t out_cap);

// Version query, handy for diagnostics.
C99_LEETCODE_PUBLIC_DECL const char* c99lc_version(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // C99_LEETCODE_H_INCLUDE


/*=============================================================================
   IMPLEMENTATION
  =============================================================================*/
#ifdef C99_LEETCODE_IMPLEMENTATION

// Definition macro: empty for global symbols, or 'static' when HELLOWORLD_STATIC.
#ifndef C99_LEETCODE_PUBLIC_DEF
#  ifdef C99_LEETCODE_STATIC
#    define C99_LEETCODE_PUBLIC_DEF static
#  else
#    define C99_LEETCODE_PUBLIC_DEF
#  endif
#endif

// Private namespace prefix 'c99lc__' for internal symbols.
static const char c99lc__hello_literal[] = "Hello, World!";
static const char c99lc__version_literal[] = "0.1";

C99_LEETCODE_PUBLIC_DEF const char* c99lc_helloworld(void)
{
    return c99lc__hello_literal;
}

C99_LEETCODE_PUBLIC_DEF int c99lc_helloworld_into(char* out, size_t out_cap)
{
    if (!out || out_cap == 0) return 0;
    // Simple, dependency-free copy of the known literal.
    // Keep it malloc-free per stb guidance.
    const char* s = c99lc__hello_literal;
    size_t i = 0;
    // Reserve one byte for terminator.
    while (s[i] != '\0' && i + 1 < out_cap) {
        out[i] = s[i];
        ++i;
    }
    out[i < out_cap ? i : out_cap - 1] = '\0';
    return (int)i;
}

C99_LEETCODE_PUBLIC_DEF const char* c99lc_version(void)
{
    return c99lc__version_literal;
}

#endif // C99_LEETCODE_IMPLEMENTATION


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2025 Dmytro Zharii
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
