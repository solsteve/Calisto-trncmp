env = Environment()

env=Environment(
    CPPPATH='src/include',
    CPPDEFINES=['foo'],
    LIBS=['stdc++','m'],
    SCONS_CXX_STANDARD='c++11')

env.StaticLibrary('trncmp', Glob('src/source/*.cc'))
