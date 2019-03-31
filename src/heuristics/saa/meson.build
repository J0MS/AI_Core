project(
  'saa_tsp',
  'cpp',
  default_options : ['cpp_std=c++14'],version : '0.1')

libs = include_directories('lib')

sqlite3 = dependency('sqlite3')

src = ['src/saa.cpp', 'src/matrix.cpp', 'src/Main.cpp']

executable('main_saa',src,include_directories : libs,dependencies : sqlite3)


testing_saa = executable('testing', 'src/testing.cpp',
                     include_directories : libs)

test('Factorial of 0 is 1 (fail)', testing_saa)                     
test('Factorials of 1 and higher are computed (pass)', testing_saa)
