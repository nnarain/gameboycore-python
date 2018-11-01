
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

    // STL container types
    py::bind_vector<GameboyCorePython::ByteList>(m, "ByteList");
    py::bind_vector<GameboyCorePython::PixelList>(m, "PixelList");
    py::bind_vector<GameboyCorePython::SpriteList>(m, "SpriteList");

    // GPU Pixel
    py::class_<gb::Pixel>(m, "Pixel", R"pbdoc(Pixel, contained in scanlines)pbdoc")
        .def_readwrite("r", &gb::Pixel::r, R"pbdoc(red)pbdoc")
        .def_readwrite("g", &gb::Pixel::g, R"pbdoc(green)pbdoc")
        .def_readwrite("b", &gb::Pixel::b, R"pbdoc(blue)pbdoc");

    // Joypad enums
    py::enum_<gb::Joy::Key>(m, "JoypadKey", R"pbdoc(Joypad Key)pbdoc")
        .value("KEY_RIGHT",  gb::Joy::Key::RIGHT)
        .value("KEY_LEFT",   gb::Joy::Key::LEFT)
        .value("KEY_UP",     gb::Joy::Key::UP)
        .value("KEY_DOWN",   gb::Joy::Key::DOWN)
        .value("KEY_A",      gb::Joy::Key::A)
        .value("KEY_B",      gb::Joy::Key::B)
        .value("KEY_SELECT", gb::Joy::Key::SELECT)
        .value("KEY_START",  gb::Joy::Key::START);

    // Joypad Action enums
    py::enum_<GameboyCorePython::KeyAction>(m, "KeyAction", R"pbdoc(Joypad Key Event)pbdoc")
        .value("ACTION_PRESS", GameboyCorePython::KeyAction::PRESS)
        .value("ACTION_RELEASE", GameboyCorePython::KeyAction::RELEASE);

    // Sprites
    py::class_<gb::Sprite>(m, "Sprite", R"pbdoc(OAM Sprite)pbdoc")
        .def_readwrite("y",      &gb::Sprite::y,      R"pbdoc(Sprite y position)pbdoc")
        .def_readwrite("x",      &gb::Sprite::x,      R"pbdoc(Sprite x position)pbdoc")
        .def_readwrite("tile",   &gb::Sprite::tile,   R"pbdoc(Sprite tile code)pbdoc")
        .def_readwrite("attr",   &gb::Sprite::attr,   R"pbdoc(Sprite attributes)pbdoc")
        .def_readwrite("height", &gb::Sprite::height, R"pbdoc(Sprite height (8 or 16 px))pbdoc");

    // Premade color themes
    py::enum_<gb::GameboyCore::ColorTheme>(m, "ColorTheme", R"pbdoc(Pre-configured color themes)pbdoc")
        .value("DEFAULT", gb::GameboyCore::ColorTheme::DEFAULT)
        .value("GOLD", gb::GameboyCore::ColorTheme::GOLD)
        .value("GREEN", gb::GameboyCore::ColorTheme::GREEN);

    // CPU Status
    py::class_<gb::CPU::Status>(m, "CPUStatus", R"pbdoc(CPU Registers)pbdoc")
        .def_readonly("a",                  &gb::CPU::Status::a,                   R"pbdoc(A register (general purpose))pbdoc")
        .def_readonly("f",                  &gb::CPU::Status::f,                   R"pbdoc(F register (flags))pbdoc")
        .def_readonly("af",                 &gb::CPU::Status::af,                  R"pbdoc(AF register (Combined A and F registers))pbdoc")
        .def_readonly("b",                  &gb::CPU::Status::b,                   R"pbdoc(B register (general purpose))pbdoc")
        .def_readonly("c",                  &gb::CPU::Status::c,                   R"pbdoc(C register (general purpose))pbdoc")
        .def_readonly("bc",                 &gb::CPU::Status::bc,                  R"pbdoc(BC register (Combined B and C registers))pbdoc")
        .def_readonly("d",                  &gb::CPU::Status::d,                   R"pbdoc(D register (general purpose))pbdoc")
        .def_readonly("e",                  &gb::CPU::Status::e,                   R"pbdoc(E register (general purpose))pbdoc")
        .def_readonly("de",                 &gb::CPU::Status::de,                  R"pbdoc(DE register (Combined D and E registers))pbdoc")
        .def_readonly("h",                  &gb::CPU::Status::h,                   R"pbdoc(H register (general purpose))pbdoc")
        .def_readonly("l",                  &gb::CPU::Status::l,                   R"pbdoc(L register (general purpose))pbdoc")
        .def_readonly("hl",                 &gb::CPU::Status::hl,                  R"pbdoc(HL register (Combined H and L registers))pbdoc")
        .def_readonly("pc",                 &gb::CPU::Status::pc,                  R"pbdoc(PC register (Program counter))pbdoc")
        .def_readonly("sp",                 &gb::CPU::Status::sp,                  R"pbdoc(SP register (Stack pointer))pbdoc")
        .def_readonly("halt",               &gb::CPU::Status::halt,                R"pbdoc(Flag indicating CPU halt)pbdoc")
        .def_readonly("stopped",            &gb::CPU::Status::stopped,             R"pbdoc(Flag indicating CPU is stopped)pbdoc")
        .def_readonly("ime",                &gb::CPU::Status::ime,                 R"pbdoc(Master interrupts enabled flag)pbdoc")
        .def_readonly("enabled_interrupts", &gb::CPU::Status::enabled_interrupts, R"pbdoc(Bit field for enabled interrupts)pbdoc")
        .def(py::pickle(
            [](const gb::CPU::Status& cpu)
            {
                return py::make_tuple(cpu.a, cpu.f, cpu.af, cpu.b, cpu.c, cpu.bc, cpu.d, cpu.e, cpu.de, cpu.h, cpu.l, cpu.hl,
                                      cpu.pc, cpu.sp, cpu.halt, cpu.stopped, cpu.ime, cpu.enabled_interrupts);
            },
            [](py::tuple t)
            {
                gb::CPU::Status cpu;
                cpu.a                  = t[0].cast<uint8_t>();
                cpu.f                  = t[1].cast<uint8_t>();
                cpu.af                 = t[2].cast<uint16_t>();
                cpu.b                  = t[3].cast<uint8_t>();
                cpu.c                  = t[4].cast<uint8_t>();
                cpu.bc                 = t[5].cast<uint16_t>();
                cpu.d                  = t[6].cast<uint8_t>();
                cpu.e                  = t[7].cast<uint8_t>();
                cpu.de                 = t[8].cast<uint16_t>();
                cpu.h                  = t[9].cast<uint8_t>();
                cpu.l                  = t[10].cast<uint8_t>();
                cpu.hl                 = t[11].cast<uint16_t>();
                cpu.pc                 = t[12].cast<uint16_t>();
                cpu.sp                 = t[13].cast<uint16_t>();
                cpu.halt               = t[14].cast<bool>();
                cpu.stopped            = t[15].cast<bool>();
                cpu.ime                = t[16].cast<bool>();
                cpu.enabled_interrupts = t[17].cast<bool>();

                return cpu;
            }
        ));

    // GameboyCore
    py::class_<GameboyCorePython>(m, "GameboyCore", R"pbdoc(Instance of a GameboyCore)pbdoc")
        .def(py::init<>())
        .def("open",                       &GameboyCorePython::open,                     R"pbdoc(Load the specified ROM file)pbdoc")
        .def("input",                      &GameboyCorePython::input,                    R"pbdoc(Joypad input)pbdoc")
        .def("update",                     &GameboyCorePython::update,                   R"pbdoc(Run n steps of the CPU)pbdoc")
        .def("emulate_frame",              &GameboyCorePython::emulateFrame,             R"pbdoc(Emulate a single frame)pbdoc")
        .def("register_scanline_callback", &GameboyCorePython::registerScanlineCallback, R"pbdoc(Register a callback for scanlines)pbdoc")
        .def("register_vblank_callback",   &GameboyCorePython::registerVBlankCallback,   R"pbdoc(Register a callback for vblank)pbdoc")
        .def("register_audio_callback",    &GameboyCorePython::registerAudioCallback,    R"pbdoc(Register a callbackf for audio samples)pbdoc")
        .def("get_cpu_state",              &GameboyCorePython::getCPUStatus,             R"pbdoc(Get the current CPU state)pbdoc")
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

