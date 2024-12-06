#include "dyn_string.h"
#include "stdlib.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define _4k (4 * 1024)

struct DynString {
    size_t allocated;
    char *end;
    char *buffer;
};

dyn_string new_dyn_string() {
    dyn_string str = (dyn_string)malloc(sizeof(struct DynString));
    if (str == NULL) {
        return NULL;
    }

    str->buffer = (char *)malloc(_4k);
    if (str->buffer == NULL) {
        free(str);
        return NULL;
    }

    str->buffer[0] = '\0';
    str->allocated = _4k;
    str->end = str->buffer;

    return str;
}

int concat_dyn_string(dyn_string str, const char *to_concat) {
    size_t used_space = (str->end - str->buffer);
    size_t free_space = str->allocated - used_space + 1;
    size_t to_concat_size = strlen(to_concat) + 1;

    if (free_space < to_concat_size) {
        str->allocated *= 2;
        str->buffer = realloc(str->buffer, str->allocated);
        if (str->buffer == NULL) {
            printf("[ERROR] Could not reallcoate dynamic string!\n");
            return 1;
        }
        str->end = str->buffer + used_space;
        free_space = str->allocated - used_space + 1;
    }

    strncat(str->end, to_concat, to_concat_size - 1);
    str->end += to_concat_size - 1;

    return 0;
}

/**
 * Trims and returns the dynamic string into a C char * array.
 */
char *unpack_and_free_dyn_string(dyn_string str) {
    char *res = realloc(str->buffer, str->end - str->buffer + 1);

    if (res == NULL) {
        printf("[ERROR] Failed to trim dynamic string buffer!\n");
        return NULL;
    }

    free(str);

    return res;
}
