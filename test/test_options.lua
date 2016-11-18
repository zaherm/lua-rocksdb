local rocksdb = require("rocksdb")

for k,v in pairs(rocksdb) do
  print(k..": "..tostring(v))
end

local options = rocksdb.options({
  increase_parallelism = 1,
  create_if_missing = true
})
assert(options.class == "options")

local db = rocksdb.open(options, "/tmp/rocksdb.test")

local readoptions = rocksdb.readoptions()
local writeoptions = rocksdb.writeoptions()
print(db.options)
