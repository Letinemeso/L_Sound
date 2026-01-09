#include <Devices/Device.h>

using namespace LSound;


Device::Device(Device&& _from)
{
    m_device = _from.m_device;
    _from.m_device = nullptr;
}
