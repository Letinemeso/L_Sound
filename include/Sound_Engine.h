#pragma once

#include <al.h>
#include <alc.h>

#include <vec3.hpp>


namespace LSound
{

    class Sound_Engine
    {
    private:
        ALCdevice* m_device = nullptr;
        ALCcontext* m_context = nullptr;

    private:
        glm::vec3 m_listener_position = { 0.0f, 0.0f, 0.0f };

    private:
        Sound_Engine();

        Sound_Engine(const Sound_Engine&) = delete;
        Sound_Engine(Sound_Engine&&) = delete;

    public:
        ~Sound_Engine();

    public:
        static Sound_Engine& get_instance();

    public:
        inline const ALCdevice* device() const { return m_device; }
        inline const ALCcontext* context() const { return m_context; }

        inline const glm::vec3& listener_position() const { return m_listener_position; }

    public:
        void set_listener_position(const glm::vec3& _position);

    };

}
