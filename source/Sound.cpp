#include <Sound.h>

using namespace LSound;


Sound::Sound()
{

}

Sound::~Sound()
{
    if(!m_sound_data)
        return;

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



void Sound::play()
{
    L_ASSERT(m_sound_data);

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
}
