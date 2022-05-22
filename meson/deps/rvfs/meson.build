rvfs_lib = library('rvfs', 
    '../../../src/rvfs.c',
    '../../../submodules/assertf.h/assertf.h',
    install: false, dependencies: [
        assertf_dep, 
      ], 
    include_directories: [
        '../../../include',
        '../../../src',
    ]
)

rvfs_dep = declare_dependency(include_directories: [
        '../../../include',
        '../../../src',
    ], link_with: rvfs_lib
)

deps += rvfs_dep
