hash_lib = library('hash', 
  '../../../deps/hash/hash.c', 
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../deps/hash',
  ]
)

hash_dep = declare_dependency(include_directories: [
        '../../../deps/hash',
    ], 
    link_with: hash_lib
)

deps += hash_dep
