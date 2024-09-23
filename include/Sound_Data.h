#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LSound
{

    struct Raw_Sound_Data
    {
        char* data = nullptr;
        unsigned int size = 0;
        int format = 0;
        int frequency = 0;
    };


    class Sound_Data : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LSound::Sound_Data, LV::Variable_Base)

    private:
        friend class Sound_Data_Stub;

    private:
        Raw_Sound_Data m_raw_sound_data;

    public:
        Sound_Data(const Sound_Data&) = delete;
        Sound_Data(Sound_Data&&) = delete;

    protected:
        Sound_Data();

    public:
        ~Sound_Data();

    public:
        inline void set_raw_data(const Raw_Sound_Data& _data) { m_raw_sound_data = _data; }
        inline const Raw_Sound_Data& raw_data() const { return m_raw_sound_data; }

    };


    class Sound_Data_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LSound::Sound_Data_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, sound_file_path)
        FIELDS_END

    public:
        std::string sound_file_path;

    protected:
        INIT_BUILDER_STUB(Sound_Data)

    };

}


