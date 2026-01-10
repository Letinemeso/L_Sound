#pragma once

#include <string>

#include <L_Debug/L_Debug.h>

#include <Devices/Device.h>
#include <Sound_Data.h>


namespace LSound
{

    struct Input_Device_Settings
    {
        std::string device_name;
        unsigned int frequency;
        ALCenum format;
        float max_capture_duration = -1.0f;
        float raw_volume_multiplier = 1.0f;

        Input_Device_Settings(float _max_capture_duration) { L_ASSERT(_max_capture_duration > 0.0f); max_capture_duration = _max_capture_duration; }

        static Input_Device_Settings voip_standard(float _max_capture_duration)
        {
            Input_Device_Settings result(_max_capture_duration);
            result.frequency = 16000;
            result.format = AL_FORMAT_MONO16;
            return result;
        }
    };


    class Input_Device : public Device
    {
    private:
        Input_Device_Settings m_settings;

        bool m_capture_in_process = false;

        using Sample_Extraction_Func = LST::Function<float(char*, unsigned int)>;
        using Sample_Rewrite_Func = LST::Function<void(char*, unsigned int, float)>;
        Sample_Extraction_Func m_extract_sample_func;
        Sample_Rewrite_Func m_rewrite_sample_func;

    public:
        Input_Device(const Input_Device_Settings& _settings);
        Input_Device(Input_Device&& _from);

        ~Input_Device();

    public:
        inline const Input_Device_Settings& settings() const { return m_settings; }
        inline bool is_capturing() const { return m_capture_in_process; }

    private:
        unsigned int M_bytes_per_sample() const;
        unsigned int M_sample_byte_size() const;
        unsigned int M_max_sample_value(unsigned int _sample_size) const;

        void M_boost_raw_data_volume(char* _data, unsigned int _samples_amount) const;

    public:
        void start_capture();
        void stop_capture();

        Sound_Data* extract_capture() const;

    };

}
