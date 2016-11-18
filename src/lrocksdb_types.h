#ifndef LROCKSDB_TYPES_H
#define LROCKSDB_TYPES_H
#include "lrocksdb.h"

typedef  struct {
 rocksdb_options_t *options;
} lrocksdb_options_t;

typedef  struct {
 rocksdb_writeoptions_t *writeoptions;
} lrocksdb_writeoptions_t;

typedef  struct {
 rocksdb_readoptions_t *readoptions;
} lrocksdb_readoptions_t;

typedef struct {
  rocksdb_t *db;
  lrocksdb_options_t *options;
} lrocksdb_t;


#endif
