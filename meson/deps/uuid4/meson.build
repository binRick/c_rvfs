uuid4_lib = library('uuid4', 
    '../../../submodules/uuid4/src/uuid4.c', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/uuid4/src',
    ]
)

uuid4_dep = declare_dependency(include_directories: [
        '../../../submodules/uuid4/src',
    ], link_with: uuid4_lib
)

deps += uuid4_dep
