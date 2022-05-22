log_lib = library('log', 
    '../../../submodules/log.c/src/log.c',
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/log.c/src',
    ]
)

log_dep = declare_dependency(include_directories: [
        '../../../submodules/log.c/src',
    ], link_with: log_lib
)

deps += log_dep
