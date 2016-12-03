
/**
    \file gameboycore_python.cpp
    \brief Gameboy Core Python Wrapper
    \author Natesh Narain <nnaraindev@gmail.com>
    \date Dec 1 2016
*/
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

namespace python = boost::python;

const char* greet()
{
    return "Hello World";
}

BOOST_PYTHON_MODULE(gameboycore)
{
    python::def("greet", greet);
}
