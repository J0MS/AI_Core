project(
  'saa',
  'cpp', default_options : ['cpp_std=c++11'])

lib = include_directories('include')

sqlite3 = dependency('sqlite3')

src = ['src/saa.cpp', 'src/matrix.cpp', 'src/Main.cpp']

executable(
  'saa',
  src,
  include_directories : lib,
  dependencies : sqlite3)
