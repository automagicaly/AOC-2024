#ifndef DYN_STRING
#define DYN_STRING

typedef struct DynString *dyn_string;

/**
 * Creates new dynamic string.
 *
 * Returns:
 *  - NULL on failure to allocate memory.
 *  - A new dynamic string on success.
 */
dyn_string new_dyn_string();

/**
 * Concats a C string into the end of the dynamic string.
 *
 * Parameters:
 *   - str: Dynamic string to concatenated to.
 *   - to_concat: C string to be used on the operation.
 *
 * Returns:
 *  - 0 on success.
 *  - 1 on any error.
 */
int concat_dyn_string(dyn_string str, const char *to_concat);

/**
 * Trims and returns the dynamic string into a C char * array.
 */
char *unpack_and_free_dyn_string(dyn_string str);

#endif
