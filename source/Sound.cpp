#include <Sound.h>

#include <Math_Stuff.h>

using namespace LSound;


bool Sound::Settings::operator==(const Settings& _other) const
{
    return
        LEti::Math::floats_are_equal(volume, _other.volume) &&
        LEti::Math::floats_are_equal(play_speed, _other.play_speed) &&
        on_loop == _other.on_loop &&
        LEti::Math::vecs_are_equal(position, _other.position) &&
        LEti::Math::floats_are_equal(fade_start_distance, _other.fade_start_distance) &&
        LEti::Math::floats_are_equal(fade_end_distance, _other.fade_end_distance);
}

bool Sound::Settings::operator!=(const Settings& _other) const
{
    return !(*this == _other);
}





Sound::Sound()
{

}

Sound::~Sound()
{
    if(!m_sound_data)
        return;

    if(is_playing())
        stop();

    alDeleteSources(1, &m_source);
    alDeleteBuffers(1, &m_buffer);
}



void Sound::set_sound_data(const Sound_Data* _ptr)
{
    if(m_sound_data)
    {
        alDeleteSources(1, &m_source);
        alDeleteBuffers(1, &m_buffer);
    }

    m_sound_data = _ptr;

    if(!m_sound_data)
        return;

    alGenBuffers(1, &m_buffer);
    alBufferData(m_buffer, m_sound_data->raw_data().format, m_sound_data->raw_data().data, m_sound_data->raw_data().size, m_sound_data->raw_data().frequency);

    alGenSources(1, &m_source);
    alSourcei(m_source, AL_BUFFER, m_buffer);
}



bool Sound::is_playing() const
{
    L_ASSERT(m_sound_data);

    ALint sourceState;
    alGetSourcei(m_source, AL_SOURCE_STATE, &sourceState);

    return sourceState == AL_PLAYING;
}



void Sound::M_apply_settings()
{
    L_ASSERT(m_sound_data);

    alSourcef(m_source, AL_GAIN, m_modifiable_settings.volume);
    alSourcef(m_source, AL_PITCH, m_modifiable_settings.play_speed);
    alSourcei(m_source, AL_LOOPING, m_modifiable_settings.on_loop ? AL_TRUE : AL_FALSE);
    alSourcefv(m_source, AL_POSITION, &m_modifiable_settings.position[0]);
    alSourcef(m_source, AL_REFERENCE_DISTANCE, m_modifiable_settings.fade_start_distance);
    alSourcef(m_source, AL_MAX_DISTANCE, m_modifiable_settings.fade_end_distance);

    m_current_settings = m_modifiable_settings;
}



void Sound::play()
{
    L_ASSERT(m_sound_data);

    if(m_current_settings != m_modifiable_settings)
        M_apply_settings();

    alSourcePlay(m_source);
}

void Sound::pause()
{
    L_ASSERT(m_sound_data);

    alSourcePause(m_source);
}

void Sound::stop()
{
    L_ASSERT(m_sound_data);

    alSourceStop(m_source);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Sound_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Sound_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(sound_data_name.size() > 0);

    const Sound_Data* sound_data = resources_manager->get_resource<Sound_Data>(sound_data_name);
    product->set_sound_data(sound_data);

    Sound::Settings settings;
    settings.volume = volume;
    settings.play_speed = play_speed;
    settings.on_loop = on_loop;
    settings.position = position;
    settings.fade_start_distance = fade_start_distance;
    settings.fade_end_distance = fade_end_distance;

    product->set_settings(settings);
}
