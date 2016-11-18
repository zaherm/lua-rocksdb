#include "lrocksdb_options.h"
LUALIB_API int lrocksdb_options_reg(lua_State *L) {
  lrocksdb_createmeta(L, "options", options_reg);
  return 1;
}

LUALIB_API int lrocksdb_writeoptions_reg(lua_State *L) {
  lrocksdb_createmeta(L, "writeoptions", writeoptions_reg);
  return 1;
}

LUALIB_API int lrocksdb_readoptions_reg(lua_State *L) {
  lrocksdb_createmeta(L, "readoptions", readoptions_reg);
  return 1;
}


void lrocksdb_options_set_from_table(lua_State *L, int index, rocksdb_options_t *opt) {
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

lrocksdb_options_t *lrocksdb_get_options(lua_State *L, int index) {
  lrocksdb_options_t *o = (lrocksdb_options_t *) luaL_checkudata(L, index, "options");
  luaL_argcheck(L, o != NULL, index, "options expected");
  return o;
}

LUALIB_API int lrocksdb_options_create(lua_State *L) {
  lrocksdb_options_t *o = (lrocksdb_options_t *) lua_newuserdata(L, sizeof(lrocksdb_options_t));
  o->options = rocksdb_options_create();
  lrocksdb_setmeta(L, "options");
  if(lua_istable(L, 1)) {
    lrocksdb_options_set_from_table(L, 1, o->options);
  }
  return 1;
}

LUALIB_API int lrocksdb_options_set(lua_State *L) {
  lrocksdb_options_t *o = lrocksdb_get_options(L, 1);
  if(lua_istable(L, 1)) {
    lrocksdb_options_set_from_table(L, 1, o->options);
  }
  return 0;
}

LUALIB_API int lrocksdb_options_destroy(lua_State *L) {
  lrocksdb_options_t *o = lrocksdb_get_options(L, 1);
  if(o->options != NULL) {
    rocksdb_options_destroy(o->options);
    o->options = NULL;
    o = NULL;
  }
  return 0;
}

/* write options */
lrocksdb_writeoptions_t *lrocksdb_get_writeoptions(lua_State *L, int index) {
  lrocksdb_writeoptions_t *o = (lrocksdb_writeoptions_t *) luaL_checkudata(L, index, "writeoptions");
  luaL_argcheck(L, o != NULL, index, "writeoptions expected");
  return o;
}

void lrocksdb_writeoptions_set_from_table(lua_State *L, int index, rocksdb_writeoptions_t *opt) {
  lua_pushvalue(L, index);
  lua_pushnil(L);
  while (lua_next(L, -2))
  {
    lua_pushvalue(L, -2);
    //TODO: const char *key = lua_tostring(L, -1);
    lua_pop(L, 2);
  }
  lua_pop(L, 1);
}

LUALIB_API int lrocksdb_writeoptions_create(lua_State *L) {
  lrocksdb_writeoptions_t *o = (lrocksdb_writeoptions_t *) lua_newuserdata(L, sizeof(lrocksdb_writeoptions_t));
  o->writeoptions = rocksdb_writeoptions_create();
  lrocksdb_setmeta(L, "writeoptions");
  if(lua_istable(L, 1)) {
    lrocksdb_writeoptions_set_from_table(L, 1, o->writeoptions);
  }
  return 1;
}

LUALIB_API int lrocksdb_writeoptions_destroy(lua_State *L) {
  lrocksdb_writeoptions_t *wo = lrocksdb_get_writeoptions(L, 1);
  if(wo != NULL && wo->writeoptions != NULL) {
    rocksdb_writeoptions_destroy(wo->writeoptions);
    wo->writeoptions = NULL;
    wo = NULL;
  }
  return 0;
}
/* read options */
lrocksdb_readoptions_t *lrocksdb_get_readoptions(lua_State *L, int index) {
  lrocksdb_readoptions_t *o = (lrocksdb_readoptions_t *) luaL_checkudata(L, index, "readoptions");
  luaL_argcheck(L, o != NULL, index, "readoptions expected");
  return o;
}

void lrocksdb_readoptions_set_from_table(lua_State *L, int index, rocksdb_readoptions_t *opt) {
  lua_pushvalue(L, index);
  lua_pushnil(L);
  while (lua_next(L, -2))
  {
    lua_pushvalue(L, -2);
   //TODO: const char *key = lua_tostring(L, -1);
    lua_pop(L, 2);
  }
  lua_pop(L, 1);
}

LUALIB_API int lrocksdb_readoptions_create(lua_State *L) {
  lrocksdb_readoptions_t *o = (lrocksdb_readoptions_t *) lua_newuserdata(L, sizeof(lrocksdb_readoptions_t));
  o->readoptions = rocksdb_readoptions_create();
  lrocksdb_setmeta(L, "readoptions");
  if(lua_istable(L, 1)) {
    lrocksdb_readoptions_set_from_table(L, 1, o->readoptions);
  }
  return 1;
}

LUALIB_API int lrocksdb_readoptions_destroy(lua_State *L) {
  lrocksdb_readoptions_t *ro = lrocksdb_get_readoptions(L, 1);
  if(ro != NULL && ro->readoptions != NULL) {
    rocksdb_readoptions_destroy(ro->readoptions);
    ro->readoptions = NULL;
    ro = NULL;
  }
  return 1;
}

