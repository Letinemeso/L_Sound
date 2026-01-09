#include <Devices/Output_Device.h>

#include <L_Debug/L_Debug.h>

using namespace LSound;


Output_Device::Output_Device() : Device()
{
    m_device = alcOpenDevice(nullptr);
    L_ASSERT(m_device);
}

Output_Device::Output_Device(Output_Device&& _from) : Device((Device&&)_from)
{

}


Output_Device::~Output_Device()
{
    alcCloseDevice(m_device);
}
