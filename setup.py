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

from setuptools import setup
from setuptools.extension import Extension

# Boost Configuration
try:
    BOOST_ROOT = os.environ['BOOST_ROOT']
except KeyError as e:
    print(('Error: BOOST_ROOT is not setup'))
    exit(1)

BOOST_INCLUDE_DIR = BOOST_ROOT
BOOST_LIB_DIR     = os.path.join(BOOST_ROOT, 'stage', 'lib')

print('== Boost Configuration ==')
print('-- BOOST_ROOT:        %s' % BOOST_ROOT)
print('-- BOOST_INCLUDE_DIR: %s' % BOOST_INCLUDE_DIR)
print('-- BOOST_LIB_DIR:     %s' % BOOST_LIB_DIR)
