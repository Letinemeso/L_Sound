#pragma once

#include <al.h>

#include <Resources_Manager.h>

#include <Sound_Data.h>


namespace LSound
{

    class Sound : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LSound::Sound, LV::Variable_Base);

    private:
        const Sound_Data* m_sound_data = nullptr;

        ALuint m_buffer = 0;
        ALuint m_source = 0;

    public:
        Sound();
        ~Sound();

    public:
        void set_sound_data(const Sound_Data* _ptr);

    public:
        bool is_playing() const;

    public:
        void play();
        void pause();
        void stop();

    };


    class Sound_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LSound::Sound_Stub, LV::Builder_Stub);

        INIT_FIELDS
        ADD_FIELD(std::string, sound_data_name)
        FIELDS_END

    public:
        const LEti::Resources_Manager* resources_manager = nullptr;

    public:
        std::string sound_data_name;

    public:
        INIT_BUILDER_STUB(Sound);

    };

}
