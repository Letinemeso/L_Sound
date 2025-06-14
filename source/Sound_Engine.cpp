#include <Sound_Engine.h>

#include <L_Debug/L_Debug.h>

using namespace LSound;


Sound_Engine::Sound_Engine()
{
    m_device = alcOpenDevice(nullptr);
    L_ASSERT(m_device);

    m_context = alcCreateContext(m_device, nullptr);
    L_ASSERT(m_context);

    alcMakeContextCurrent(m_context);
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
}

Sound_Engine::~Sound_Engine()
{
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}



Sound_Engine& Sound_Engine::get_instance()
{
    static Sound_Engine instance;
    return instance;
}



void Sound_Engine::set_listener_position(const glm::vec3& _position)
{
    m_listener_position = _position;
    alListenerfv(AL_POSITION, &_position[0]);
}
