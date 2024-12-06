#include "dyn_string.h"
#include "lua/install/include/lauxlib.h"
#include "lua/install/include/lua.h"
#include "lua/install/include/lualib.h"
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *regex_replace(const char *string, const char *pattern,
                    const char *replace) {
    dyn_string result;
    regex_t regex;
    regmatch_t match;
    char *buffer;
    char *buffer_back;
    size_t buffer_size = strlen(string) + 1;

    buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        printf("[ERROR] Could not allocate memory for the buffer\n");
        return NULL;
    }
    buffer_back = buffer;
    strncpy(buffer, string, buffer_size);

    result = new_dyn_string();
    if (result == NULL) {
        printf("[ERROR] Could not allocate memory for the new string\n");
        return NULL;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("[ERROR] Could not compile regex!\n");
        return NULL;
    }

    while (regexec(&regex, buffer, 1, &match, 0) != REG_NOMATCH) {
        buffer[match.rm_so] = '\0';
        concat_dyn_string(result, buffer);
        concat_dyn_string(result, replace);
        buffer += match.rm_eo;
    }
    concat_dyn_string(result, buffer);

    free(buffer_back);

    return unpack_and_free_dyn_string(result);
}

int lua_regex_replace(lua_State *L) {
    const char *string = luaL_checkstring(L, 1);
    const char *pattern = luaL_checkstring(L, 2);
    const char *replace = luaL_checkstring(L, 3);

    char *replaced = regex_replace(string, pattern, replace);

    if (replaced == NULL) {
        lua_pushstring(L, "[ERROR] Failed to replace string.\n");
        lua_error(L);
        return 0;
    }

    lua_pushstring(L, replaced);

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("[ERROR] Missing input script path\n");
        return -1;
    }

    lua_State *L;
    L = luaL_newstate();
    if (!L) {
        return -1;
    }
    luaL_openlibs(L);

    // exposes regex_replace function.
    lua_pushcfunction(L, lua_regex_replace);
    lua_setglobal(L, "regex_replace");

    if (luaL_loadfile(L, argv[1]) != LUA_OK) {
        printf("[ERROR] Failed to load script\n");
        return -1;
    }
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        printf("[ERROR] Failed to run script: %s\n", lua_tostring(L, -1));
        return -1;
    }

    lua_close(L);
    return 0;
}
