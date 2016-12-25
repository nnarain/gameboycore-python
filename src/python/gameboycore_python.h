#ifndef GAMEBOYCORE_PYTHON_H
#define GAMEBOYCORE_PYTHON_H

#include <boost/python.hpp>

#include <gameboycore/gameboycore.h>
#include <fstream>
#include <vector>
#include <array>
#include <functional>
#include <cstdint>

class GameboyCorePython : public gb::GameboyCore
{
public:
    using PixelList = std::vector<gb::Pixel>;

    template<class T, int N>
    static boost::python::list arrayToList(const std::array<T, N>& arr)
    {
        auto vec = std::vector<T>(arr.begin(), arr.end());
        auto iter = boost::python::iterator<std::vector<T>>()(vec);

        return boost::python::list(iter);
    }

    GameboyCorePython()
    {
    }

    void registerGpuCallback(boost::python::object callable)
    {
        gpuCallback_ = callable;
        this->getGPU()->setRenderCallback(
            std::bind(&GameboyCorePython::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2)
        );
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

    ~GameboyCorePython()
    {
    }

private:
    void scanlineCallback(const gb::GPU::Scanline& scanline, int line)
    {
        auto list = arrayToList(scanline);
        gpuCallback_(list, line);
    }

private:
    boost::python::object gpuCallback_;
};

#endif // GAMEBOYCORE_PYTHON_H
