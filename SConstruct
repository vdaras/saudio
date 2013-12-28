import os

#create environment
env = Environment()
Export('env')

#Add command line build options
AddOption('--debug-build',
          dest = 'debug_build',
          action = 'store_true',
          help = 'Build with debug symbols enabled',
          default = False)

AddOption('--profile-build',
          dest = 'profile_build',
          action = 'store_true',
          help = 'Build with profile symbols enabled (Overrides --debug-build)',
          default = False)

#Get command line options
if GetOption('debug_build'):
    debug = 1
else:
    debug = 0

if GetOption('profile_build'):
    profile = 1
else:
    profile = 0

#Process command line options
compiler_flags = ['-std=c++11']
linker_flags = []

if profile:
   compiler_flags.append('-pg')
   linker_flags.append('-pg')
elif debug:
   compiler_flags.append('-O0')
   compiler_flags.append('-g')
   compiler_flags.append('-Wall')
else:
   compiler_flags.append('-O3')

env.AppendUnique(CPPPATH = '#src/')
env.AppendUnique(CXXFLAGS = compiler_flags)
env.AppendUnique(LINKFLAGS = linker_flags)

#Check library availability
conf = Configure(env)

required_libs = []

if os.name == 'posix' :
    required_libs.append('pthread')

for lib in required_libs:
    if not conf.CheckLib(lib):
        print lib + " library missing, exiting.."
        Exit(1)

#Run SConscript files
env.SConscript(os.path.join('src', 'SConscript'))

#Build
Import('source_files')

for source in source_files:
    print source

env.Program(target = 'saudio',
            source = source_files,
            variant_dir='build')
