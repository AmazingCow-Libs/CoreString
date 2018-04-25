/*
Copyright (C) 2014 insane coder (http://insanecoding.blogspot.com/, http://asprintf.insanecoding.org/)

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "asprintf.h"

/*
//Define the following, and this will work with MSVC or other platforms that lack va_copy, but a simple copying of va_list does the trick
#ifndef va_copy
#define va_copy(dest, src) dest = src
#endif
*/


#define insane_free(ptr) { free(ptr); ptr = 0; }


int
insanecoding::vasprintf(char **strp, const char *fmt, va_list ap)
{
    va_list ap2;
    va_copy(ap2, ap);

    // Calculate how much space we needed on this buffer.
    auto size_needed = vsnprintf(nullptr, 0, fmt, ap2);
    auto result      = -1;

    if((size_needed >= 0) && (size_needed < INT_MAX)) { // Ok, we have a valid size.
        *strp = (char *)malloc(size_needed + 1); // +1 for null
        if(*strp) { // We could allocate memory...
            auto chars_written = vsnprintf(*strp, size_needed+1, fmt, ap); // +1 for null
            if(chars_written < 0) { // Error...
                // COWTODO(n2omatt): How handle errors here??
                insane_free(*strp);
            } else {
                result = chars_written;
            }
        }
    } else { // Ops.. we don't have a valid size.
        // COWTODO(n2omatt): How handle errors here???
        *strp = nullptr;
    }

    va_end(ap2);
    return result;
}