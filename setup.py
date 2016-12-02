#!/usr/bin/env python
#
# Gameboy Core Python Bindings
#
# @author Natesh Narain
# @date Dec 1 2016
#

# install setuptools
import ez_setup
ez_setup.use_setuptools()

from setuptools import setup, find_packages
from setuptools.extension import Extension

setup(
    name="gameboycore-python",
    version="0.0.0",
    packages=find_packages('src'),
    package_dir={'':'src'},

    scripts=[],

    # dependencies
    install_requires=[],

    # Authoring Information
    author="Natesh Narain",
    author_email="nnaraindev@gmail.com",
    description="Python bindings for Gameboy Core",
    license="MIT",
    keywords="gameboy emulator emulation",
    url="https://github.com/nnarain/gameboycore-python"
)
