project(
  'aco_mvcp',
  'cpp', 
  default_options : ['cpp_std=c++17', 'buildtype=debug'],version : '0.1')

libs = include_directories('lib')

src = ['src/aco.cpp', 'src/matrix.cpp', 'src/Main.cpp']
src_test = ['src/aco.cpp', 'src/matrix.cpp', 'src/testing.cpp']

executable('main_aco',src,include_directories : libs)

testing_aco = executable('testing', src_test,include_directories : libs )
