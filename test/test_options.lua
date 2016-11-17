local rocksdb = require("rocksdb")

for k,v in pairs(rocksdb) do
  print(k..": "..tostring(v))
end

local options = rocksdb.options()
assert(options.class == "options")
options:increase_parallelism(1)
options:set_create_if_missing(true)

local db = rocksdb.open(options, "/tmp/rocksdb.test")