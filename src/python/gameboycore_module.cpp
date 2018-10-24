
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

    m.doc() = R"pbdoc(
        GameboyCore Python API
        ----------------------

        .. currentmodule:: gameboycore

        .. autosummary::
            :toctree: _generate

            GameboyCore
            JoypadKey
            KeyAction
            Pixel
            Sprite
            ColorTheme
    )pbdoc";

    py::class_<gb::Pixel>(m, "Pixel", R"pbdoc(Pixel, contained in scanlines)pbdoc")
        .def_readwrite("r", &gb::Pixel::r, R"pbdoc(red)pbdoc")
        .def_readwrite("g", &gb::Pixel::g, R"pbdoc(green)pbdoc")
        .def_readwrite("b", &gb::Pixel::b, R"pbdoc(blue)pbdoc");

    py::enum_<gb::Joy::Key>(m, "JoypadKey", R"pbdoc(Joypad Key)pbdoc")
        .value("KEY_RIGHT",  gb::Joy::Key::RIGHT)
        .value("KEY_LEFT",   gb::Joy::Key::LEFT)
        .value("KEY_UP",     gb::Joy::Key::UP)
        .value("KEY_DOWN",   gb::Joy::Key::DOWN)
        .value("KEY_A",      gb::Joy::Key::A)
        .value("KEY_B",      gb::Joy::Key::B)
        .value("KEY_SELECT", gb::Joy::Key::SELECT)
        .value("KEY_START",  gb::Joy::Key::START);

    py::enum_<GameboyCorePython::KeyAction>(m, "KeyAction", R"pbdoc(Joypad Key Event)pbdoc")
        .value("ACTION_PRESS", GameboyCorePython::KeyAction::PRESS)
        .value("ACTION_RELEASE", GameboyCorePython::KeyAction::RELEASE);

    py::class_<gb::Sprite>(m, "Sprite", R"pbdoc(OAM Sprite)pbdoc")
        .def_readwrite("y",      &gb::Sprite::y, R"pbdoc(Sprite y position)pbdoc")
        .def_readwrite("x",      &gb::Sprite::x, R"pbdoc(Sprite x position)pbdoc")
        .def_readwrite("tile",   &gb::Sprite::tile, R"pbdoc(Sprite tile code)pbdoc")
        .def_readwrite("attr",   &gb::Sprite::attr, R"pbdoc(Sprite attributes)pbdoc")
        .def_readwrite("height", &gb::Sprite::height, R"pbdoc(Sprite height (8 or 16 px))pbdoc");

    py::enum_<gb::GameboyCore::ColorTheme>(m, "ColorTheme", R"pbdoc(Pre-configured color themes)pbdoc")
        .value("DEFAULT", gb::GameboyCore::ColorTheme::DEFAULT)
        .value("GOLD", gb::GameboyCore::ColorTheme::GOLD)
        .value("GREEN", gb::GameboyCore::ColorTheme::GREEN);

    py::bind_vector<GameboyCorePython::ByteList>(m, "ByteList");
    py::bind_vector<GameboyCorePython::PixelList>(m, "PixelList");
    py::bind_vector<GameboyCorePython::SpriteList>(m, "SpriteList");

    py::class_<GameboyCorePython>(m, "GameboyCore", R"pbdoc(Instance of a GameboyCore)pbdoc")
        .def(py::init<>())
        .def("open",                       &GameboyCorePython::open,                     R"pbdoc(Load the specified ROM file)pbdoc")
        .def("input",                      &GameboyCorePython::input,                    R"pbdoc(Joypad input)pbdoc")
        .def("update",                     &GameboyCorePython::update,                   R"pbdoc(Run n steps of the CPU)pbdoc")
        .def("emulate_frame",              &GameboyCorePython::emulateFrame,             R"pbdoc(Emulate a single frame)pbdoc")
        .def("register_scanline_callback", &GameboyCorePython::registerScanlineCallback, R"pbdoc(Register a callback for scanlines)pbdoc")
        .def("register_vblank_callback",   &GameboyCorePython::registerVBlankCallback,   R"pbdoc(Register a callback for vblank)pbdoc")
        .def("register_audio_callback",    &GameboyCorePython::registerAudioCallback,    R"pbdoc(Register a callbackf for audio samples)pbdoc")
        .def("get_background_hash",        &GameboyCorePython::getBackgroundHash,        R"pbdoc(Get a hash of the background tile map)pbdoc")
        .def("get_background_tilemap",     &GameboyCorePython::getBackgroundTileMap,     R"pbdoc(Get the background tile map)pbdoc")
        .def("get_sprite_cache",           &GameboyCorePython::getSpriteCache,           R"pbdoc(Get OAM sprites)pbdoc")
        .def("set_color_theme",            &GameboyCorePython::setColorTheme,            R"pbdoc(Set a pre-configured color theme)pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}

