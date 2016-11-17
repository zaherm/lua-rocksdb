#ifndef LROCKSDB_HELPERS_H
#define LROCKSDB_HELPERS_H
#include "lauxlib.h"
#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
LUALIB_API void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup);
#endif
LUALIB_API int lrocksdb_createmeta(lua_State *L, const char *name, const luaL_Reg *methods);
LUALIB_API void lrocksdb_setmeta(lua_State *L, const char *name);
#endif
