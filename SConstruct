import os

FABRIC_MAJOR_VERSION = os.environ['FABRIC_MAJOR_VERSION']
FABRIC_MINOR_VERSION = os.environ['FABRIC_MINOR_VERSION']
env = Environment()
env.Append(CPPPATH = ['/usr/include', '/usr/local/include', os.environ["FABRIC_SPLICEAPI_DIR"]])
env.Append(LIBPATH = ['/usr/lib','/usr/local/lib', os.environ['BOOST_LIBRARY_DIR'], os.environ['FABRIC_SPLICEAPI_DIR']])
env.Append(CPPDEFINES=['FEC_STATIC', 'FECS_STATIC'])
env.Append(LIBS=[
    'FabricSplice-%s_ss' % FABRIC_MINOR_VERSION, 'FabricCore-%s_s' % FABRIC_MAJOR_VERSION, 'boost_filesystem', 'boost_system', 'boost_thread','GL', 'pthread', 'dl'
])


p = env.Program('helloworld', Glob('*.cpp'))