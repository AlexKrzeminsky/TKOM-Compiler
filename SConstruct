BOOST_LIB_DIR = '/usr/include/boost/lib'
BOOST_INCLUDE_DIR = '/usr/include/boost/include'

def initial_scons_config():
    Decider('MD5-timestamp')

def fill_env_flags(env):
    env['BOOST_INCLUDES'] = '/usr/include/boost'
    env['BOOST_LIBS'] = '/usr/include/boost/lib'
    env.Append(CCFLAGS=['-Wall', '-Wextra', '-Wpedantic', '-Werror'])
    env.Append(CCFLAGS=['-std=c++14', '-BOOST_ALL_DYN_LINK', '-lboost_log', '-g'])

    env.Append(LIBS=['pthread', 'boost_log', 'boost_system', 'boost_coroutine'])
    env.Append(LINKFLAGS = ['-BOOST_ALL_DYN_LINK'])
    env.Append()

def create_env():
    env = Environment()
    Export('env')
    fill_env_flags(env)
    return env

def build_executable(env):
    p = env.SConscript('src/SConscript', duplicate=0)
    env.Install('./', p)

initial_scons_config()

env = create_env()

build_executable(env)
