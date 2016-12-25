
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

    enum_<gb::Joy::Key>("JoypadKey")
        .value("KEY_RIGHT",  gb::Joy::Key::RIGHT)
        .value("KEY_LEFT",   gb::Joy::Key::LEFT)
        .value("KEY_UP",     gb::Joy::Key::UP)
        .value("KEY_DOWN",   gb::Joy::Key::DOWN)
        .value("KEY_A",      gb::Joy::Key::A)
        .value("KEY_B",      gb::Joy::Key::B)
        .value("KEY_SELECT", gb::Joy::Key::SELECT)
        .value("KEY_START",  gb::Joy::Key::START);

    enum_<GameboyCorePython::KeyAction>("KeyAction")
        .value("ACTION_PRESS", GameboyCorePython::KeyAction::PRESS)
        .value("ACTION_RELEASE", GameboyCorePython::KeyAction::RELEASE);

    class_<GameboyCorePython>("GameboyCore")
        .def("update", &GameboyCorePython::update)
        .def("open", &GameboyCorePython::open)
        .def("input", &GameboyCorePython::input)
        .def("registerGpuCallback", &GameboyCorePython::registerGpuCallback);
}
