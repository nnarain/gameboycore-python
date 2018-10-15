
/**
    \file gameboycore_python.cpp
    \brief Gameboy Core Python Wrapper
    \author Natesh Narain <nnaraindev@gmail.com>
    \date Dec 1 2016
*/

#include "gameboycore_python.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

PYBIND11_MAKE_OPAQUE(GameboyCorePython::ByteList);
PYBIND11_MAKE_OPAQUE(GameboyCorePython::PixelList);
PYBIND11_MAKE_OPAQUE(GameboyCorePython::SpriteList);


PYBIND11_MODULE(gameboycore, m) {
    namespace py = pybind11;

    py::class_<gb::Pixel>(m, "Pixel")
        .def_readwrite("r", &gb::Pixel::r)
        .def_readwrite("g", &gb::Pixel::g)
        .def_readwrite("b", &gb::Pixel::b);

    py::enum_<gb::Joy::Key>(m, "JoypadKey")
        .value("KEY_RIGHT",  gb::Joy::Key::RIGHT)
        .value("KEY_LEFT",   gb::Joy::Key::LEFT)
        .value("KEY_UP",     gb::Joy::Key::UP)
        .value("KEY_DOWN",   gb::Joy::Key::DOWN)
        .value("KEY_A",      gb::Joy::Key::A)
        .value("KEY_B",      gb::Joy::Key::B)
        .value("KEY_SELECT", gb::Joy::Key::SELECT)
        .value("KEY_START",  gb::Joy::Key::START);

    py::enum_<GameboyCorePython::KeyAction>(m, "KeyAction")
        .value("ACTION_PRESS", GameboyCorePython::KeyAction::PRESS)
        .value("ACTION_RELEASE", GameboyCorePython::KeyAction::RELEASE);

    py::class_<gb::Sprite>(m, "Sprite")
        .def_readwrite("y",      &gb::Sprite::y)
        .def_readwrite("x",      &gb::Sprite::x)
        .def_readwrite("tile",   &gb::Sprite::tile)
        .def_readwrite("attr",   &gb::Sprite::attr)
        .def_readwrite("height", &gb::Sprite::height);

    py::bind_vector<GameboyCorePython::ByteList>(m, "ByteList");
    py::bind_vector<GameboyCorePython::PixelList>(m, "PixelList");
    py::bind_vector<GameboyCorePython::SpriteList>(m, "SpriteList");

    py::class_<GameboyCorePython>(m, "GameboyCore")
        .def(py::init<>())
        .def("open",                       &GameboyCorePython::open)
        .def("input",                      &GameboyCorePython::input)
        .def("update",                     &GameboyCorePython::update)
        .def("register_scanline_callback", &GameboyCorePython::registerScanlineCallback)
        .def("register_vblank_callback",   &GameboyCorePython::registerVBlankCallback)
        .def("get_background_hash",        &GameboyCorePython::getBackgroundHash)
        .def("get_background_tilemap",     &GameboyCorePython::getBackgroundTileMap)
        .def("get_sprite_cache",           &GameboyCorePython::getSpriteCache);

}

