project(
  'qt-material-widgets',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=gnu++17'],
)

cc = meson.get_compiler('cpp')

dep = declare_dependency(
  dependencies : cc.find_library('components', dirs : [meson.current_source_dir()]),
  include_directories : include_directories('components'),
)

