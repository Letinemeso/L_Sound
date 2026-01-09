#pragma once

#include <al.h>
#include <alc.h>


namespace LSound
{

    class Device
    {
    protected:
        ALCdevice* m_device = nullptr;

    public:
        Device() { }
        Device(const Device& _other) = delete;

        Device(Device&& _from);

        virtual ~Device() { }

    public:
        ALCdevice* device() const { return m_device; }

    };

}
