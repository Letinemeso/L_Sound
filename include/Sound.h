#pragma once

#include <al.h>
#include <vec3.hpp>

#include <Resources_Manager.h>

#include <Sound_Data.h>


namespace LSound
{

    class Sound : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LSound::Sound, LV::Variable_Base);

    public:
        struct Settings
        {
            float volume = -1.0f;
            float play_speed = 1.0f;
            bool on_loop = false;
            glm::vec3 position = {0.0f, 0.0f, 0.0f};
            float fade_start_distance = 0.0f;
            float fade_end_distance = 1.0f;

            bool operator==(const Settings& _other) const;
            bool operator!=(const Settings& _other) const;
        };

    private:
        const Sound_Data* m_sound_data = nullptr;

        ALuint m_buffer = 0;
        ALuint m_source = 0;

        Settings m_current_settings;
        Settings m_modifiable_settings;

    public:
        Sound();
        ~Sound();

    public:
        inline Settings& settings() { return m_modifiable_settings; }
        inline const Settings& current_settings() const { return m_current_settings; }
        inline void set_settings(const Settings& _value) { m_modifiable_settings = _value; }

    public:
        void set_sound_data(const Sound_Data* _ptr);

    public:
        bool is_playing() const;

    private:
        void M_apply_settings();

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
        ADD_FIELD(float, volume)
        ADD_FIELD(float, play_speed)
        ADD_FIELD(bool, on_loop)
        ADD_FIELD(glm::vec3, position)
        ADD_FIELD(float, fade_start_distance)
        ADD_FIELD(float, fade_end_distance)
        FIELDS_END

    public:
        const LEti::Resources_Manager* resources_manager = nullptr;

    public:
        std::string sound_data_name;

        float volume = 1.0f;
        float play_speed = 1.0f;
        bool on_loop = false;
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        float fade_start_distance = 0.0f;
        float fade_end_distance = 1.0f;

    public:
        INIT_BUILDER_STUB(Sound);

    };

}
