#include "lua/install/include/lauxlib.h"
#include "lua/install/include/lua.h"
#include "lua/install/include/lualib.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Missing input script path");
    return -1;
  }

  lua_State *L;
  L = luaL_newstate();
  if (!L) {
    return -1;
  }
  luaL_openlibs(L);

  if (luaL_loadfile(L, argv[1]) != LUA_OK) {
    printf("Failed to load script");
    return -1;
  }
  if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
    printf("Failed to run script: %s\n", lua_tostring(L, -1));
    return -1;
  }

  lua_close(L);
  return 0;
}
