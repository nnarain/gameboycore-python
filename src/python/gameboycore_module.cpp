
/**
    \file gameboycore_python.cpp
    \brief Gameboy Core Python Wrapper
    \author Natesh Narain <nnaraindev@gmail.com>
    \date Dec 1 2016
*/
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#include "gameboycore_python.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(gameboycore)
{
    class_<gb::APU, boost::noncopyable>("APU", no_init);
    class_<gb::CPU, boost::noncopyable>("CPU", no_init);
    class_<gb::GPU, boost::noncopyable>("GPU", no_init);
    class_<gb::Joy, boost::noncopyable>("Joy", no_init);
    class_<gb::MMU, boost::noncopyable>("MMU", no_init);


    class_<GameboyCorePython>("GameboyCore")
        .def("apu", &GameboyCorePython::apu, return_internal_reference<>())
        .def("cpu", &GameboyCorePython::cpu, return_internal_reference<>())
        .def("gpu", &GameboyCorePython::gpu, return_internal_reference<>())
        .def("joy", &GameboyCorePython::joy, return_internal_reference<>())
        .def("mmu", &GameboyCorePython::mmu, return_internal_reference<>());
}
