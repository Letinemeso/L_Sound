#include <Sound_Engine.h>

#include <L_Debug/L_Debug.h>
#include <Stuff/Message_Translator.h>

#include <Sound_Messages.h>
#include <Devices/Output_Device.h>

using namespace LSound;


Sound_Engine::Sound_Engine()
{
    m_output_device = new Output_Device;

    m_context = alcCreateContext(m_output_device->device(), nullptr);
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
    delete m_output_device;
}



void Sound_Engine::set_listener_volume_multiplier(float _value)
{
    L_ASSERT(_value >= 0.0f);

    m_listener_volume_multiplier = _value;
    alListenerf(AL_GAIN, _value);
}

void Sound_Engine::set_listener_position(const glm::vec3& _position)
{
    m_listener_position = _position;
    alListenerfv(AL_POSITION, &_position[0]);
}

void Sound_Engine::set_listener_orientation(const glm::vec3& _forward, const glm::vec3& _top)
{
    m_listener_look_forward = _forward;
    m_listener_look_top = _top;

    float data[6] = { _forward[0], _forward[1], _forward[2], _top[0], _top[1], _top[2] };

    alListenerfv(AL_ORIENTATION, data);
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
