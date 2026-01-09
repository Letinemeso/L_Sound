#pragma once

#include <Devices/Device.h>


namespace LSound
{

    class Output_Device : public Device
    {
    public:
        Output_Device();
        Output_Device(Output_Device&& _from);

        ~Output_Device();

    };

}
