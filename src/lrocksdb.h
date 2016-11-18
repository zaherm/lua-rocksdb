#ifndef LROCKSDB_H
#define LROCKSDB_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "lauxlib.h"

#include "rocksdb/c.h"
#include "lrocksdb_helpers.h"
#include "lrocksdb_types.h"
#include "lrocksdb_options.h"
#define LROCKSDB_VERSION "lua-rocksdb 0.0.1"
#define LROCKSDB_COPYRIGHT "Copyright (C) 2016, Zaher Marzuq"
#define LROCKSDB_DESCRIPTION "RocksDB binding for Lua"


LUALIB_API int lrocksdb_put(lua_State *L);
LUALIB_API int lrocksdb_get(lua_State *L);
LUALIB_API int lrocksdb_close(lua_State *L);

static const struct luaL_Reg  lrocksdb_db_reg[] = {
  { "put", lrocksdb_put },
  { "get", lrocksdb_get },
  { "close", lrocksdb_close },
  { NULL, NULL }
};

#endif
