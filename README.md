lua-rocksdb
===
Lua binding for RocksDB

Installation
==
* Install RocksDB (make shared_lib), download from: https://github.com/facebook/rocksdb
* Update the Makefile if needed to point at the correct include/lib paths

Usage
==
```lua
  local rocksdb = require("rocksdb")
  local options = rocksdb.options({
    create_if_missing = true
  })
  local db = rocksdb.open(options, "/tmp/test.rocksdb")
  local writeoptions = rocksdb.writeoptions()
  local readoptions = rocksdb.readoptions()
  db:put(writeoptions, "key", "value")
  print(db:get(readoptions, "key"))
  db:close()
```
