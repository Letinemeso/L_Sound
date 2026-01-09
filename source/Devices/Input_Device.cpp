#include <Devices/Input_Device.h>

#include <Stuff/Math_Stuff.h>

#include <Sound_Engine.h>

using namespace LSound;


Input_Device::Input_Device(const Input_Device_Settings& _settings) : Device(), m_settings(_settings)
{
    Sound_Engine::instance();   //  in case context has not been created

    L_ASSERT(m_settings.max_capture_duration > 0.0f);

    const char* device_name = nullptr;
    if(m_settings.device_name.size() > 0)
        device_name = m_settings.device_name.c_str();

    unsigned int buffer_size_samples = m_settings.frequency * m_settings.max_capture_duration;
    L_ASSERT(buffer_size_samples > 0);

    m_device = alcCaptureOpenDevice(device_name, m_settings.frequency, m_settings.format, buffer_size_samples);
    L_ASSERT(m_device);

    if(M_sample_byte_size() == 1)
    {
        m_extract_sample_func = [](char* _data, unsigned int _index)->float
        {
            return (float)_data[_index];
        };
        m_rewrite_sample_func = [](char* _data, unsigned int _index, float _value)
        {
            short unsigned int value = _value;
            _data[_index] = value;
        };
    }
    else
    {
        m_extract_sample_func = [](char* _data, unsigned int _index)->float
        {
            short unsigned int* data = (short unsigned int*)_data;
            return (float)data[_index];
        };
        m_rewrite_sample_func = [](char* _data, unsigned int _index, float _value)
        {
            short unsigned int value = _value;
            short unsigned int* data = (short unsigned int*)_data;
            data[_index] = value;
        };
    }
}

Input_Device::Input_Device(Input_Device&& _from) : Device((Device&&)_from), m_settings(_from.m_settings)
{
    m_extract_sample_func = _from.m_extract_sample_func;
    m_rewrite_sample_func = _from.m_rewrite_sample_func;
}


Input_Device::~Input_Device()
{
    alcCaptureCloseDevice(m_device);
}



unsigned int Input_Device::M_bytes_per_sample() const
{
    if(m_settings.format == AL_FORMAT_MONO8)
        return 1;
    if(m_settings.format == AL_FORMAT_STEREO8)
        return 2;
    if(m_settings.format == AL_FORMAT_MONO16)
        return 2;
    if(m_settings.format == AL_FORMAT_STEREO16)
        return 4;

    L_ASSERT(false);
    return 0;
}

unsigned int Input_Device::M_sample_byte_size() const
{
    if(m_settings.format == AL_FORMAT_MONO8 || m_settings.format == AL_FORMAT_STEREO8)
        return 1;
    if(m_settings.format == AL_FORMAT_MONO16 || m_settings.format == AL_FORMAT_STEREO16)
        return 2;

    L_ASSERT(false);
    return 0;
}

unsigned int Input_Device::M_max_sample_value(unsigned int _sample_size) const
{
    if(_sample_size == 1)
        return 0x000000FF;
    if(_sample_size == 2)
        return 0x0000FFFF;

    L_ASSERT(false);
    return 0;
}


void Input_Device::M_boost_raw_data_volume(char* _data, unsigned int _samples_amount) const
{
    if(LST::Math::floats_are_equal(m_settings.raw_volume_multiplier, 1.0f))
        return;

    unsigned int sample_size = M_sample_byte_size();
    unsigned int max_sample_value = M_max_sample_value(sample_size);
    float max_sample_value_float = (float)max_sample_value;

    unsigned int values_amount = _samples_amount;
    if(m_settings.format == AL_FORMAT_STEREO8 || m_settings.format == AL_FORMAT_STEREO16)
        values_amount *= 2;

    for(unsigned int i = 0; i < values_amount; ++i)
    {
        float value = m_extract_sample_func(_data, i);

        value *= m_settings.raw_volume_multiplier;
        if(value > max_sample_value_float)
            value = max_sample_value_float;

        m_rewrite_sample_func(_data, i, value);
    }
}



void Input_Device::start_capture()
{
    m_capture_in_process = true;
    alcCaptureStart(m_device);
}

void Input_Device::stop_capture()
{
    m_capture_in_process = false;
    alcCaptureStop(m_device);
}


Sound_Data* Input_Device::extract_capture() const
{
    L_ASSERT(!m_capture_in_process);

    ALCint samples_captured;
    alcGetIntegerv(m_device, ALC_CAPTURE_SAMPLES, sizeof(samples_captured), &samples_captured);

    if(samples_captured <= 0)
        return nullptr;

    unsigned int bytes_per_sample = M_bytes_per_sample();
    unsigned int raw_data_size = bytes_per_sample * samples_captured;
    Sound_Data* result = new Sound_Data;

    Raw_Sound_Data raw_data;
    raw_data.frequency = m_settings.frequency;
    raw_data.format = m_settings.format;
    raw_data.size = raw_data_size;

    raw_data.data = new char[raw_data_size];
    alcCaptureSamples(m_device, raw_data.data, samples_captured);

    M_boost_raw_data_volume(raw_data.data, samples_captured);

    result->set_raw_data(raw_data);

    return result;
}
