#ifndef GAMEBOYCORE_PYTHON_H
#define GAMEBOYCORE_PYTHON_H

#include <pybind11/pybind11.h>

#include <gameboycore/gameboycore.h>
#include <fstream>
#include <vector>
#include <array>
#include <functional>
#include <cstdint>
#include <stdexcept>

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

    void registerScanlineCallback(pybind11::object callable)
    {
        setCallable(scanline_callback_, callable);
    }

    void registerVBlankCallback(pybind11::object callable)
    {
        setCallable(vblank_callback_, callable);
    }

    void registerAudioCallback(pybind11::object callable)
    {
        setCallable(audio_callback_, callable);
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
        // open file, and seek to end
        std::ifstream file(rom_file, std::ios::binary | std::ios::ate);
        // get file size
        auto size = file.tellg();
        // create a buffer for the file
        std::vector<uint8_t> buffer;
        buffer.resize(size);
        // seek to begin and read file into buffer
        file.seekg(0, std::ios::beg);
        file.read((char*)&buffer[0], size);
        // load ROM
        this->loadROM(&buffer[0], size);

        // setup callbacks
        setupCallbacks();
    }

    gb::CPU::Status getCPUStatus()
    {
        return this->getCPU()->getStatus();
    }

    ByteList getBatteryRam()
    {
        return this->getMMU()->getBatteryRam();
    }

    std::size_t getBackgroundHash()
    {
        return this->getGPU()->getBackgroundHash();
    }

    ByteList getBackgroundTileMap()
    {
        return this->getGPU()->getBackgroundTileMap();
    }

    SpriteList getSpriteCache()
    {
        return this->getGPU()->getSpriteCache();
    }

    ~GameboyCorePython()
    {
    }

private:
    void scanlineCallback(const gb::GPU::Scanline& scanline, int line)
    {
        auto list = arrayToList<gb::Pixel, 160>(scanline);

        if (scanline_callback_)
            scanline_callback_(list, line);
    }

    void vblankCallback()
    {
        if (vblank_callback_)
            vblank_callback_();
    }

    void audioCallback(int16_t s1, int16_t s2)
    {
        if (audio_callback_)
            audio_callback_(s1, s2);
    }

    void setupCallbacks()
    {
        this->getGPU()->setRenderCallback(
            std::bind(&GameboyCorePython::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2)
        );
        this->getGPU()->setVBlankCallback(std::bind(&GameboyCorePython::vblankCallback, this));
        this->getAPU()->setAudioSampleCallback(std::bind(&GameboyCorePython::audioCallback, this, std::placeholders::_1, std::placeholders::_2));
    }

    void setCallable(pybind11::object& obj, pybind11::object& callable)
    {
        if (PyCallable_Check(callable.ptr()))
        {
            obj = callable;
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "Object is not callable");
            throw std::runtime_error("Object is not callable");
        }
    }

    template<class T, int N>
    static std::vector<T> arrayToList(const std::array<T, N>& arr)
    {
        std::vector<T> vec(arr.begin(), arr.end());
        return vec;
    }

private:
    pybind11::object scanline_callback_;
    pybind11::object vblank_callback_;
    pybind11::object audio_callback_;
};

#endif // GAMEBOYCORE_PYTHON_H
