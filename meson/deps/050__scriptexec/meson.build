scriptexec_lib = library('scriptexec', '../../../submodules/c_scriptexec/src/scriptexec.c', install: false, dependencies: [fsio_dep, stringbuffer_dep], 
  include_directories: [
    '../../../submodules/c_stringfn/include',
    '../../../deps/fs',
    '../../../submodules/c_stringfn/include',
    '../../../submodules/c_scriptexec/include',
    '../../../submodules/c_scriptexec/src',
  ]
)
scriptexec_dep = declare_dependency(include_directories: ['../../../submodules/c_scriptexec/include'], link_with: scriptexec_lib)
deps += scriptexec_dep
