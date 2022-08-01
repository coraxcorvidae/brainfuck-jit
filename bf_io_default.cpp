// Copyright 2014 Jon Ripley
// See "LICENSE" file for details.

#include <string>

#include "bf_io_default.h"

bool BrainfuckIODefault::bf_write(void *, char c) {
    return putchar(c) != EOF;
}

char BrainfuckIODefault::bf_read(void *) {
    int c = getchar();
    if (c == EOF) {
        return 0; 
    } else {
        return c;
    }
}
