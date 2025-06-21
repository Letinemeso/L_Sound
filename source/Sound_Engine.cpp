#include <Sound_Engine.h>

#include <L_Debug/L_Debug.h>
#include <Stuff/Message_Translator.h>

#include <Sound_Messages.h>

using namespace LSound;


Sound_Engine::Sound_Engine()
{
    m_device = alcOpenDevice(nullptr);
    L_ASSERT(m_device);

    m_context = alcCreateContext(m_device, nullptr);
    L_ASSERT(m_context);

    alcMakeContextCurrent(m_context);
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

    LST::Message_Translator& mt = LST::Message_Translator::instance();
    mt.register_message_type<Message__Stop_All_Sounds>();
    mt.register_message_type<Message__Pause_All_Sounds>();
    mt.register_message_type<Message__Continue_All_Sounds>();
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


void Sound_Engine::stop_all_sounds()
{
    Message__Stop_All_Sounds msg;
    LST::Message_Translator::instance().translate(msg);
}

void Sound_Engine::pause_all_sounds()
{
    Message__Pause_All_Sounds msg;
    LST::Message_Translator::instance().translate(msg);
}

void Sound_Engine::continue_all_sounds()
{
    Message__Continue_All_Sounds msg;
    LST::Message_Translator::instance().translate(msg);
}
