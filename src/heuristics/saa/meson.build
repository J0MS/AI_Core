project(
  'saa_tsp',
  'cpp',
  default_options : ['cpp_std=c++11'],version : '0.1')

libs = include_directories('lib')

sqlite3 = dependency('sqlite3')

src = ['src/saa.cpp', 'src/matrix.cpp', 'src/Main.cpp']

executable('main_saa',src,include_directories : libs,dependencies : sqlite3)
