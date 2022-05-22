assertf_lib = library('assertf', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/assertf.h',
    ]
)

assertf_dep = declare_dependency(include_directories: [
        '../../../submodules/assertf.h',
    ], link_with: assertf_lib
)

deps += assertf_dep
