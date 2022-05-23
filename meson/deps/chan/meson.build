chan_lib = library('chan', 
    '../../../submodules/chan/src/queue.c', 
    '../../../submodules/chan/src/chan.c', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/chan/src',
    ]
)

chan_dep = declare_dependency(include_directories: [
        '../../../submodules/chan/src',
    ], link_with: chan_lib
)

deps += chan_dep
