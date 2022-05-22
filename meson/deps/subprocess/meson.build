subprocess_lib = library('subprocess', 
  '../../../submodules/subprocess.h/subprocess.h', 
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../submodules/subprocess.h',
  ]
)
subprocess_dep = declare_dependency(include_directories: [
    '../../../submodules/subprocess.h',
  ], 
  link_with: subprocess_lib)

deps += subprocess_dep
