import os

FABRIC_MAJOR_VERSION = os.environ['FABRIC_MAJOR_VERSION']
FABRIC_MINOR_VERSION = os.environ['FABRIC_MINOR_VERSION']
env = Environment()
env.Append(CPPPATH = [os.environ["FABRIC_SPLICE_API_DIR"]])
env.Append(LIBPATH = [os.environ["FABRIC_SPLICE_API_DIR"]])
env.Append(CPPDEFINES=['FEC_STATIC', 'FECS_STATIC'])


env.Append(LIBS=["pthread", "dl"])

#Fabric Engine libs
env.Append(LIBS= ["libFabricCore-%s.a" % (FABRIC_MAJOR_VERSION), "libFabricSplice-%s_s.a" % (FABRIC_MINOR_VERSION)])


p = env.Program('helloworld', Glob('*.cpp'))