#include "lrocksdb_options.h"
LUALIB_API int lrocksdb_options_reg(lua_State *L) {
  lrocksdb_createmeta(L, "options", options_reg);
  return 1;
}

lrocksdb_options_t *lrockdb_options_get(lua_State *L, int index) {
  lrocksdb_options_t *o = (lrocksdb_options_t *) luaL_checkudata(L, index, "options");       
  luaL_argcheck(L, o != NULL, index, "options expected");                        
  return o;
}

LUALIB_API int lrockdb_options_create(lua_State *L) {
  lrocksdb_options_t *o = (lrocksdb_options_t *) lua_newuserdata(L, sizeof(lrocksdb_options_t));
  o->options = rocksdb_options_create();
  lrocksdb_setmeta(L, "options");
  return 1;
}

LUALIB_API int lrocksdb_options_increase_parallelism(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_options_get(L, 1);
  int cpus = luaL_checkint(L, 2);
  rocksdb_options_increase_parallelism(o->options, cpus);
  return 0;
}

LUALIB_API int lrocksdb_options_optimize_level_style_compaction(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_options_get(L, 1);
  int lsc = luaL_checkint(L, 2);
  rocksdb_options_optimize_level_style_compaction(o->options, lsc);
  return 0;
}

LUALIB_API int lrocksdb_options_set_create_if_missing(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_options_get(L, 1);
  int cim = lua_toboolean(L, 2);
  rocksdb_options_set_create_if_missing(o->options, cim);
  return 0;
}
