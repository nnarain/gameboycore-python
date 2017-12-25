Build and Installation
======================

The easy way
------------

Windows:

    pip install gameboycore

Linux:

    easy_install gameboycore

Note: Install binary packages on Linux is broken. Install from source instead.

From source
-----------

1. Download and extract boost
2. Build boost with python

    ./bootstrap
    ./b2 --with-system --with-python python-debugging=off threading=multi variant=release link=static stage
    ./b2 --with-system --with-python python-debugging=off threading=multi variant=release link=static install

3. Set BOOST_ROOT environment variable and install extension using setup.py

    export BOOST_ROOT=/path/to/boost
    python setup.py install

4. In order to use the extension boost_python.so needs to be on the LD_LIBRARY_PATH

    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/boost/stage/lib/

5. Import the module

    import gameboycore
