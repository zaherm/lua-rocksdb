#include "lrocksdb_options.h"
LUALIB_API int lrocksdb_options_reg(lua_State *L) {
  lrocksdb_createmeta(L, "options", options_reg);
  return 1;
}

void lrockdb_options_set_from_table(lua_State *L, int index, rocksdb_options_t *opt) {
  lua_pushvalue(L, index);
  lua_pushnil(L);
  while (lua_next(L, -2))
  {
    lua_pushvalue(L, -2);
    const char *key = lua_tostring(L, -1);
    if(!strcmp(key, "increase_parallelism")) {
      int total_threads = luaL_checkint(L, -2);
      rocksdb_options_increase_parallelism(opt, total_threads);
    }
    if(!strcmp(key, "optimize_for_point_lookup")) {
      uint64_t block_cache_size_mb = luaL_checknumber(L, -2);
      rocksdb_options_optimize_for_point_lookup(opt, block_cache_size_mb);
    }
    if(!strcmp(key, "create_if_missing")) {
      unsigned char flag = lua_toboolean(L, -2);
      rocksdb_options_set_create_if_missing(opt, flag);
    }
    lua_pop(L, 2);
  }
  lua_pop(L, 1);
}

lrocksdb_options_t *lrockdb_get_options(lua_State *L, int index) {
  lrocksdb_options_t *o = (lrocksdb_options_t *) luaL_checkudata(L, index, "options");
  luaL_argcheck(L, o != NULL, index, "options expected");
  return o;
}

LUALIB_API int lrockdb_options_create(lua_State *L) {
  lrocksdb_options_t *o = (lrocksdb_options_t *) lua_newuserdata(L, sizeof(lrocksdb_options_t));
  o->options = rocksdb_options_create();
  lrocksdb_setmeta(L, "options");
  if(lua_istable(L, 1)) {
    lrockdb_options_set_from_table(L, 1, o->options);
  }
  return 1;
}

LUALIB_API int lrocksdb_options_set(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_get_options(L, 1);
  return 0;
}

LUALIB_API int lrocksdb_options_get(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_get_options(L, 1);
  return 0;
}

LUALIB_API int lrocksdb_options_destroy(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_get_options(L, 1);
  return 0;
}
