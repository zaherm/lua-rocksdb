#include "lrocksdb.h"

LUALIB_API int lrocksdb_reg(lua_State *L) {
  lrocksdb_createmeta(L, "db", lrocksdb_db_reg);
  return 1;
}

lrocksdb_t *lrocksdb_get_db(lua_State *L, int index) {
  lrocksdb_t *o = (lrocksdb_t *) luaL_checkudata(L, index, "db");
  luaL_argcheck(L, o != NULL, index, "db expected");
  return o;
}


LUALIB_API int lrocksdb_open(lua_State *L) {
  lrocksdb_options_t *o = lrocksdb_get_options(L, 1);
  const char *path = luaL_checkstring(L, 2);
  char *err = NULL;
  rocksdb_t *db = rocksdb_open(o->options, path, &err);

  if(err) {
    luaL_error(L, err);
    free(err);
    return 0;
  }

  lrocksdb_t *d = (lrocksdb_t *) lua_newuserdata(L, sizeof(lrocksdb_t));
  d->db = db;
  d->options = o;
  d->open = 1;
  lrocksdb_setmeta(L, "db");
  return 1;
}

LUALIB_API int lrocksdb_put(lua_State *L) {
  lrocksdb_t *d = lrocksdb_get_db(L, 1);

  lrocksdb_writeoptions_t *wo = lrocksdb_get_writeoptions(L, 2);
  size_t key_len, value_len;
  const char *key, *value;
  char *err = NULL;

  key = luaL_checklstring(L, 3, &key_len);
  value = luaL_checklstring(L, 4, &value_len);
  rocksdb_put(d->db, wo->writeoptions, key, key_len, value, value_len, &err);
  if(err) {
    luaL_error(L, err);
    free(err);
  }
  return 1;
}

LUALIB_API int lrocksdb_get(lua_State *L) {
  lrocksdb_t *d = lrocksdb_get_db(L, 1);
  lrocksdb_assert(L, d->open, "db is closed");
  lrocksdb_readoptions_t *ro = lrocksdb_get_readoptions(L, 2);
  size_t key_len, value_len;
  const char *key = luaL_checklstring(L, 3, &key_len);
  char *err = NULL;
  char *value = rocksdb_get(d->db, ro->readoptions, key, key_len, &value_len, &err);
  if(err) {
    luaL_error(L, err);
  }
  else {
    lua_pushlstring(L, value, value_len);
    free(value);
  }
  return 1;
}

LUALIB_API int lrocksdb_close(lua_State *L) {
  lrocksdb_t *d = lrocksdb_get_db(L, 1);
  rocksdb_close(d->db);
  d->open = 0;
  return 1;
}
static const struct luaL_Reg  lrocksdb_regs[] = {
  { "db", lrocksdb_reg },
  { "options",  lrocksdb_options_reg },
  { "writeoptions",  lrocksdb_writeoptions_reg },
  { "readoptions",  lrocksdb_readoptions_reg },
  { NULL, NULL }
};

static const struct luaL_Reg lrocksdb_funcs[] = {
  { "open", lrocksdb_open },
  { "options", lrocksdb_options_create },
  { "writeoptions", lrocksdb_writeoptions_create },
  { "readoptions", lrocksdb_readoptions_create },
  { NULL, NULL }
};


LUALIB_API int luaopen_rocksdb(lua_State *L) {
  lua_newtable(L);

  /* register classes */
  for(int i = 0; lrocksdb_regs[i].name != NULL; i++) {
    lrocksdb_regs[i].func(L);
  }

  luaL_setfuncs(L, lrocksdb_funcs, 0);

  lua_pushliteral(L, LROCKSDB_VERSION);
  lua_setfield(L, -2, "_VERSION");
  lua_pushliteral(L, LROCKSDB_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");
  lua_pushliteral(L, LROCKSDB_VERSION);
  lua_setfield(L, -2, "_DESCRIPTION");

  return 1;
}

