
/**
    \file gameboycore_python.cpp
    \brief Gameboy Core Python Wrapper
    \author Natesh Narain <nnaraindev@gmail.com>
    \date Dec 1 2016
*/
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "gameboycore_python.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(gameboycore)
{
    class_<gb::Pixel>("Pixel")
        .def_readwrite("r", &gb::Pixel::r)
        .def_readwrite("g", &gb::Pixel::g)
        .def_readwrite("b", &gb::Pixel::b);

    class_<GameboyCorePython::PixelList>("PixelList")
        .def(boost::python::vector_indexing_suite<GameboyCorePython::PixelList>());

    class_<GameboyCorePython>("GameboyCore")
        .def("update", &GameboyCorePython::update)
        .def("open", &GameboyCorePython::open)
        .def("registerGpuCallback", &GameboyCorePython::registerGpuCallback);
}
