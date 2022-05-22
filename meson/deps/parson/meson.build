parson_lib = library('parson', 
    '../../../submodules/parson/parson.c', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/parson',
    ]
)

parson_dep = declare_dependency(include_directories: [
        '../../../submodules/parson',
    ], link_with: parson_lib
)

deps += parson_dep
