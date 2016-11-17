#include "lrocksdb.h"

LUALIB_API int lrockdb_reg(lua_State *L) {
  return 1;
}

LUALIB_API int lrockdb_open(lua_State *L) {
  lrocksdb_options_t *o = lrockdb_options_get(L, 1);
  const char *path = luaL_checkstring(L, 2);
  char *err = NULL;
  rocksdb_t *db = rocksdb_open(o->options, path, &err);
 
  if(err) {
   luaL_error(L, err);
    return 0;
  }
  lrocksdb_t *d = (lrocksdb_t *) lua_newuserdata(L, sizeof(lrocksdb_t));
  d->db = db;
  d->options = o;
  lrocksdb_setmeta(L, "db");
  return 1;
}

static const struct luaL_Reg  lrocksdb_regs[] = {
  { "db", lrockdb_reg },
  { "options",  lrocksdb_options_reg },
  { NULL, NULL }
};

static const struct luaL_Reg mod_reg[] = {
  { "open", lrockdb_open },
  { "options", lrockdb_options_create },
  { NULL, NULL }
};


LUALIB_API int luaopen_rocksdb(lua_State *L) {
  lua_newtable(L);

//  lrocksdb_createmeta(L, "options", options_reg);
  for(int i = 0; lrocksdb_regs[i].name != NULL; i++) {
    lrocksdb_regs[i].func(L);
  }
  luaL_setfuncs(L, mod_reg, 0);
  
  lua_pushliteral(L, LROCKSDB_VERSION);
  lua_setfield(L, -2, "_VERSION");
  lua_pushliteral(L, LROCKSDB_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");
  lua_pushliteral(L, LROCKSDB_VERSION);
  lua_setfield(L, -2, "_DESCRIPTION");

  return 1;
}

