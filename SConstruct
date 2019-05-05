#!python
import os

# Environment
env = Environment(ENV = os.environ);

# Platform & bits
platform = ARGUMENTS.get('p', ARGUMENTS.get('platform', 'windows'));
bits = ARGUMENTS.get('b', ARGUMENTS.get('bits', '64'));
target = ARGUMENTS.get('t', ARGUMENTS.get('target', 'release'));
output = 'gdsam';
godotcpp_lib = 'godot-cpp';

if platform == 'linux':
	if ARGUMENTS.get('use_llvm', 'no') == 'yes':
		env['CXX'] = 'clang++';
	else:
		env['CXX']='g++';
	
	if target == 'debug':
		env.Append(CCFLAGS = ['-Og']);
	else:
		env.Append(CCFLAGS = ['-O3']);
	
	if bits == '64':
		env.Append(CCFLAGS = [ '-m64' ]);
		env.Append(LINKFLAGS = [ '-m64' ]);
		godotcpp_lib += '.linux.64';
	else:
		env.Append(CCFLAGS = [ '-m32' ]);
		env.Append(LINKFLAGS = [ '-m32' ]);
		godotcpp_lib += '.linux.32';

if platform == 'windows':
	if bits == '64':
		env = Environment(ENV = os.environ, TARGET_ARCH='amd64');
		godotcpp_lib += '.windows.64';
	else:
		env = Environment(ENV = os.environ, TARGET_ARCH='x86');
		godotcpp_lib += '.windows.32';
	
	if target == 'debug':
		env['CCPDBFLAGS'] = '/Zi /Fd${TARGET}.pdb'
		env['PDB']='${TARGET.base}.pdb'
		env.Append(CCFLAGS = ['-D_WIN32', '-EHsc', '/DEBUG', '-D_DEBUG', '/MDd'])
	else:
		env.Append(CCFLAGS = ['-D_WIN32', '/EHsc', '/O2', '/MD' ])

# If platform is OSX
if platform == 'osx':
	# If using Clang
	if ARGUMENTS.get('use_llvm', 'no') == 'yes':
		env['CXX'] = 'clang++'
	# Set compiler variables
	env.Append(CCFLAGS = [ '-g','-O3', '-arch', 'x86_64' ])
	env.Append(CXXFLAGS = [ '-std=c++14' ])
	env.Append(LINKFLAGS = [ '-arch', 'x86_64', '-framework', 'Cocoa', '-Wl,-undefined,dynamic_lookup' ])
	env.Append(RPATH=env.Literal("\\$$ORIGIN"))

if bits == '64':
	output += '.64';
else:
	output += '.32';

# Include dir
env.Append(CPPPATH=[
	'src',
	'thirdparty/SAM',
	'thirdparty/godot-cpp/godot_headers/',
	'thirdparty/godot-cpp/include',
	'thirdparty/godot-cpp/include/core',
	'thirdparty/godot-cpp/include/gen'
]);

# Source lists
sources = [
	'src/gdsam.cpp',
	'src/gdlibrary.cpp',
	'thirdparty/SAM/sam.cc',
    'thirdparty/SAM/createtransitions.cc',
    'thirdparty/SAM/debug.cc',
    'thirdparty/SAM/processframes.cc',
    'thirdparty/SAM/reciter.cc',
    'thirdparty/SAM/render.cc',
    'thirdparty/SAM/phoneme.cc',
    'thirdparty/SAM/state.cc',
];

# Libraries
env.Append(LIBPATH=['thirdparty/godot-cpp/bin/']);
env.Append(LIBS=[godotcpp_lib]);

library = env.SharedLibrary(target=('bin/' + output), source=sources);
Install('demo/lib/gdsam', source=library);
