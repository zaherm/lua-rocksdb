#ifndef LROCKSDB_OPTIONS_H
#define LROCKSDB_OPTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "lauxlib.h"

#include "rocksdb/c.h"
#include "lrocksdb_types.h"
#include "lrocksdb_helpers.h"

LUALIB_API int lrocksdb_options_reg(lua_State *L);
lrocksdb_options_t *lrockdb_options_get(lua_State *L, int index);
LUALIB_API int lrockdb_options_create(lua_State *L);
LUALIB_API int lrocksdb_options_increase_parallelism(lua_State *L);
LUALIB_API int lrocksdb_options_optimize_level_style_compaction(lua_State *L);
LUALIB_API int lrocksdb_options_set_create_if_missing(lua_State *L);

static const struct luaL_Reg  options_reg[] = {
  { "increase_parallelism",  lrocksdb_options_increase_parallelism },
  { "optimize_level_style_compaction", lrocksdb_options_optimize_level_style_compaction },
  { "set_create_if_missing", lrocksdb_options_set_create_if_missing },
  { NULL, NULL }
};

#endif
