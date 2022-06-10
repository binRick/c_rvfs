project('c_rvfs',
  ['c'],
  version : '0.0.1',
  default_options : [
    'warning_level=0',
    'c_std=gnu99',
  ]
)
config = configuration_data()
version = run_command('git', 'describe', '--tags')
config.set('version', version.stdout().strip())
add_project_arguments('-D_GNU_SOURCE', language : 'c')
add_project_arguments('-DDBG_H_DEF_ONCE', language : 'c')
add_project_arguments('-DDBG_H_NO_WARNING', language : 'c')
add_project_arguments('-DASSERTF_DEF_ONCE', language : 'c')
add_project_arguments('-DLOG_USE_COLOR', language : 'c')
add_project_arguments('-DLOG_LEVEL=TRACE', language : 'c')
add_project_arguments('-Wno-pragma-once-outside-header', language : 'c')
add_project_arguments('-Wno-incompatible-pointer-types', language : 'c')
#//***********************************************************/
deps = []
bin_srcs = []
cc = meson.get_compiler('c')
#//***********************************************************/
find_deps_cmd = 'find meson/deps -type f -name meson.build|xargs dirname|sort -u'
find_enabled_bins_cmd = 'make enabled-bins'
#//***********************************************************/
sh = find_program('sh', required : true)
pwd_bin = find_program('pwd', required : true)
#//***********************************************************/
find_deps = run_command(sh, '-c', find_deps_cmd, check: true).stdout().strip().split('\n')
enabled_bins = run_command(sh, '-c', find_enabled_bins_cmd, check: true).stdout().strip().split('\n')
pwd = run_command(pwd_bin, check: true).stdout().strip()
#//***********************************************************/
inc = include_directories(
  '.',
  './include', 
  './deps', 
  './submodules',
  './src', 
  './submodules/c_stringfn/include', 
  './submodules/c_fsio/include',
)
#//***********************************************************/
foreach m : find_deps
  subdir(m)
endforeach
#//***********************************************************/
test_env = environment()
test_env.set('__MESON_TEST_MODE__', '1')
test_env.set('__SH', sh.full_path())
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
if get_option('enable-binaries')
  bins = []
  foreach bin : enabled_bins
        bin_src = [
          'bins/' + bin + '.c',
        ]
        bins += {
          'name': bin,
          'executable': executable(bin, 
            [ 
              bin_src,
              files(bin_srcs),
            ],
            dependencies: [
              deps, 
            ],
            include_directories: [
              inc,
            ],
          )
        }
  endforeach
  if get_option('enable-binary-tests')
    foreach b : bins
      test(b['name'], b['executable'], args: ['--test'], env: test_env)
    endforeach
  endif
endif
#//***********************************************************/
