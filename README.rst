Gameboy Core Python
===================

.. image:: https://travis-ci.org/nnarain/gameboycore-python.svg?branch=master
    :target: https://travis-ci.org/nnarain/gameboycore-python

.. image:: https://ci.appveyor.com/api/projects/status/hatnihg8ii76hc27?svg=true
    :target: https://ci.appveyor.com/project/nnarain/gameboycore-python

.. image:: https://img.shields.io/pypi/v/gameboycore.svg
    :target: https://pypi.python.org/pypi/gameboycore

.. image:: https://readthedocs.org/projects/gameboycore-python/badge/?version=latest
    :target: http://gameboycore-python.readthedocs.io/en/latest/?badge=latest

Python Bindings for `GameboyCore <https://github.com/nnarain/gameboycore>`_

Installation
------------

On Windows:

    pip install gameboycore

On Linux:

    git clone https://github.com/nnarain/gameboycore-python
    cd gameboycore-python
    
    pip install -e .

Linux uses a source installation because PyPi does not accept `.whl` files and `pip` cannot install `.egg` files.

See online docs for installation from source instructions.

Supported Python Versions
-------------------------

====== ======= =====
Python Windows Linux
====== ======= =====
2.7    Soon    Yes
3.3    Soon    Yes
3.4    Soon    Yes
3.5    Yes     Yes
3.6    Yes     Yes
====== ======= =====

GameboyCore Python does not currently support Python version 2.7 - 3.4 on Windows since Visual Studio 9/10 do not support C++11.
