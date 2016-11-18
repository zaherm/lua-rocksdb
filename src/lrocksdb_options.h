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

lrocksdb_options_t *lrocksdb_get_options(lua_State *L, int index);
LUALIB_API int lrocksdb_options_reg(lua_State *L);
LUALIB_API int lrocksdb_options_create(lua_State *L);
LUALIB_API int lrocksdb_options_set(lua_State *L);
LUALIB_API int lrocksdb_options_get(lua_State *L);
LUALIB_API int lrocksdb_options_destroy(lua_State *L);

/* read options */
LUALIB_API int lrocksdb_readoptions_reg(lua_State *L);
LUALIB_API int lrocksdb_readoptions_create(lua_State *L);
LUALIB_API int lrocksdb_readoptions_destroy(lua_State *L);

/* write options */
LUALIB_API int lrocksdb_writeoptions_reg(lua_State *L);
LUALIB_API int lrocksdb_writeoptions_create(lua_State *L);
LUALIB_API int lrocksdb_writeoptions_destroy(lua_State *L);

/* flush options */
LUALIB_API int lrocksdb_flushoptions_create(lua_State *L);
LUALIB_API int lrocksdb_flushoptions_destroy(lua_State *L);
LUALIB_API int lrocksdb_flushoptions_set_wait(lua_State *L);

static const struct luaL_Reg options_reg[] = {
  { "set", lrocksdb_options_set },
  { "get", lrocksdb_options_get },
  { "destroy", lrocksdb_options_destroy },
  { NULL, NULL }
};

static const struct luaL_Reg writeoptions_reg[] = {
  { "destroy", lrocksdb_writeoptions_destroy },
  { NULL, NULL }
};

static const struct luaL_Reg readoptions_reg[] = {
  { "destroy", lrocksdb_readoptions_destroy },
  { NULL, NULL }
};

#endif
