project(
  'aco_mvcp',
  'cpp',
  default_options : ['cpp_std=c++17'],version : '0.1')

libs = include_directories('lib')

src = ['src/aco.cpp', 'src/matrix.cpp', 'src/Main.cpp']
src_test = ['src/aco.cpp', 'src/matrix.cpp', 'src/testing.cpp']

executable('main_aco',src,include_directories : libs)

testing_aco = executable('testing', src_test,include_directories : libs )

test('Testing input',testing_aco)
test('Testing ACO for optimum with vertex = 200, edges = 4555',testing_aco)
test('Factorial of 0 is 1 (fail)', testing_aco)
test('Factorials of 1 and higher are computed (pass)', testing_aco)
test('vectors can be sized and resized', testing_aco)
