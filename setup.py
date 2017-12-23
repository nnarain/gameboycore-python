#!/usr/bin/env python
#
# Setup for GameboyCore Python bindings
#
# @author Natesh Narain <nnaraindev@gmail.com>
# @date Dec 2 2016
#

from __future__ import print_function

import os
import sys
import platform
import sysconfig

from setuptools import setup
from setuptools.extension import Extension

def getenv(env_var, default_value):
    try:
        return os.environ[env_var]
    except KeyError as e:
        return default_value

# get this directory
DIR = os.path.dirname(os.path.realpath(__file__))

#== Boost Configuration ==
try:
    BOOST_ROOT = os.environ['BOOST_ROOT']
except KeyError as e:
    print(('Error: BOOST_ROOT is not set'))
    exit(1)

BOOST_INCLUDE_DIR   = BOOST_ROOT
BOOST_LIB_DIR       = os.path.join(BOOST_ROOT, 'stage', 'lib')
BOOST_LIB_DIR_EXTRA = os.path.join(BOOST_ROOT, getenv('BOOST_LIB_DIR', ''))

print('== Boost Configuration ==')
print('-- BOOST_ROOT:          %s' % BOOST_ROOT)
print('-- BOOST_INCLUDE_DIR:   %s' % BOOST_INCLUDE_DIR)
print('-- BOOST_LIB_DIR:       %s' % BOOST_LIB_DIR)
print('-- BOOST_LIB_DIR_EXTRA: %s' % BOOST_LIB_DIR_EXTRA)
print('')

#== Python Configuration ==
pyconfig = sysconfig.get_paths()
PYTHON_ROOT = pyconfig['data']
PYTHON_INCLUDE_DIR = pyconfig['include']
PYTHON_LIB_DIR_LINUX = pyconfig['stdlib']
PYTHON_LIB_DIR_WIN32 = os.path.join(PYTHON_ROOT, 'libs')

pyversion = "{0}.{1}".format(sys.version_info[0], sys.version_info[1])

print('== Python Configuration ==')
print('Python Version:           %s' % pyversion)
print('PYTHON_ROOT:              %s' % PYTHON_ROOT)
print('PYTHON_INCLUDE_DIR:       %s' % PYTHON_INCLUDE_DIR)
print('PYTHON_LIB_DIR_LINUX:     %s' % PYTHON_LIB_DIR_LINUX)
print('PYTHON_LIB_DIR_WIN32:     %s' % PYTHON_LIB_DIR_WIN32)
print('')

#== GameboyCore Configuration ==

GAMEBOYCORE_INCLUDE_DIR = os.path.join(DIR, 'src', 'gameboycore', 'include')

# collect sources
sources = []
for current_dir, dirs, files in os.walk(os.path.join(DIR, 'src')):
    # skip test code
    if 'tests' in dirs:
        dirs.remove('tests')
    if 'example' in dirs:
        dirs.remove('example')

    for f in files:
        ext = os.path.splitext(f)[1]
        if ext == '.cpp':
            sources.append(os.path.join(current_dir, f))

endianness = '__LITTLEENDIAN__' if sys.byteorder == 'little' else '__BIGENDIAN__'

cxx_flags = []
link_flags = []
if platform.system() == 'Linux':
    cxx_flags = ['-std=c++11','-Wno-format-security']
    link_flags = ['-l:%s' % os.path.join(BOOST_LIB_DIR, 'libboost_python.a')]

print('== GameboyCore Configuration ==')
print('-- INCLUDE_DIR: %s' % GAMEBOYCORE_INCLUDE_DIR)
print('-- ENDIAN:      %s' % endianness)
print('-- CXX_FLAGS:   %s' % cxx_flags)
print('')

#== Setup tools ==

# Extension
gameboycore_module = Extension(
    'gameboycore',
    define_macros = [
        (endianness,''),
        ('GAMEBOYCORE_STATIC', '')
    ],
    include_dirs = [
        PYTHON_INCLUDE_DIR,
        BOOST_INCLUDE_DIR,
        GAMEBOYCORE_INCLUDE_DIR
    ],

    library_dirs = [
        BOOST_LIB_DIR,
        PYTHON_LIB_DIR_LINUX,
        PYTHON_LIB_DIR_WIN32,
        BOOST_LIB_DIR_EXTRA
    ],

    libraries = ['boost_python'],

    sources = sources,

    extra_compile_args = cxx_flags,
    extra_link_args = link_flags
)

readme_file = os.path.join(DIR, 'README.rst')

setup(
    name="gameboycore",
    version="0.4.5",

    ext_modules = [gameboycore_module],

    # Authoring Information
    author="Natesh Narain",
    author_email="nnaraindev@gmail.com",
    description="Python bindings for Gameboy Core",
    long_description=open(readme_file).read(),
    license="MIT",
    keywords="gameboy emulator emulation",
    url="https://github.com/nnarain/gameboycore-python"
)
