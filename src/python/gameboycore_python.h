#ifndef GAMEBOYCORE_PYTHON_H
#define GAMEBOYCORE_PYTHON_H

#include <boost/python.hpp>

#include <gameboycore/gameboycore.h>
#include <fstream>
#include <vector>
#include <array>
#include <functional>
#include <iostream>
#include <cstdint>

class GameboyCorePython : public gb::GameboyCore
{
public:
    using PixelList  = std::vector<gb::Pixel>;
    using SpriteList = std::vector<gb::Sprite>;
    using ByteList   = std::vector<uint8_t>;

    enum class KeyAction
    {
        PRESS, RELEASE
    };

    GameboyCorePython()
    {
    }

    void registerScanlineCallback(boost::python::object callable)
    {
        if(PyCallable_Check(callable.ptr()))
        {
            scanline_callback_ = callable;
            this->getGPU()->setRenderCallback(
                std::bind(&GameboyCorePython::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2)
            );
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "Object is not callable");
            boost::python::throw_error_already_set();
        }
    }

    void registerVBlankCallback(boost::python::object callable)
    {
        if(PyCallable_Check(callable.ptr()))
        {
            vblank_callback_ = callable;
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "Object is not callable");
            boost::python::throw_error_already_set();
        }
    }

    void input(gb::Joy::Key key, KeyAction action)
    {
        if(action == KeyAction::PRESS)
        {
            this->getJoypad()->press(key);
        }
        else
        {
            this->getJoypad()->release(key);
        }
    }

    void open(const std::string& rom_file)
    {
        std::ifstream file(rom_file, std::ios::binary | std::ios::ate);
        auto size = file.tellg();

        std::vector<uint8_t> buffer;
        buffer.resize(size);

        file.seekg(0, std::ios::beg);
        file.read((char*)&buffer[0], size);

        this->loadROM(&buffer[0], size);
    }

    boost::python::list getSpriteCache()
    {
        return vectorToList(this->getGPU()->getSpriteCache());
    }

    boost::python::list getBackgroundTileMap()
    {
        return vectorToList(this->getGPU()->getBackgroundTileMap());
    }

    std::size_t getBackgroundHash()
    {
        return this->getGPU()->getBackgroundHash();
    }

    ~GameboyCorePython()
    {
    }

private:
    void scanlineCallback(const gb::GPU::Scanline& scanline, int line)
    {
        scanline_callback_(arrayToList<gb::Pixel, 160>(scanline), line);

        if(line == 143)
        {
            if(PyCallable_Check(vblank_callback_.ptr()))
            {
                vblank_callback_();
            }
        }
    }

    template<class Vector>
    static boost::python::list vectorToList(const Vector& vec)
    {
        auto iter = boost::python::iterator<Vector>()(vec);
        return boost::python::list(iter);
    }

    template<class T, int N>
    static boost::python::list arrayToList(const std::array<T, N>& arr)
    {
        std::vector<T> vec(arr.begin(), arr.end());
        return vectorToList(vec);
    }

private:
    boost::python::object scanline_callback_;
    boost::python::object vblank_callback_;
};

#endif // GAMEBOYCORE_PYTHON_H
