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
