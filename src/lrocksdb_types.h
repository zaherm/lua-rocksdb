#ifndef LROCKSDB_TYPES_H
#define LROCKSDB_TYPES_H
#include "lrocksdb.h"

typedef  struct {
 rocksdb_options_t *options;
} lrocksdb_options_t;

typedef struct {
    rocksdb_t *db;
    lrocksdb_options_t *options;
} lrocksdb_t;
#endif
