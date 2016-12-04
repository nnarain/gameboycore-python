#ifndef GAMEBOYCORE_PYTHON_H
#define GAMEBOYCORE_PYTHON_H

#include <gameboycore/gameboycore.h>

class GameboyCorePython : public gb::GameboyCore
{
public:

    GameboyCorePython()
    {
    }

    gb::APU& apu()
    {
        return *this->getAPU().get();
    }

    gb::CPU& cpu()
    {
        return *this->getCPU().get();
    }

    gb::GPU& gpu()
    {
        return *this->getGPU().get();
    }

    gb::Joy& joy()
    {
        return *this->getJoypad().get();
    }

    gb::MMU& mmu()
    {
        return *this->getMMU().get();
    }

    ~GameboyCorePython()
    {
    }

private:
};

#endif // GAMEBOYCORE_PYTHON_H
