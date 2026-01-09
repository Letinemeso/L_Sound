#pragma once

#include <al.h>
#include <alc.h>

#include <vec3.hpp>

#include <Devices/Device.h>


namespace LSound
{

    class Sound_Engine
    {
    private:
        Device* m_output_device = nullptr;
        ALCcontext* m_context = nullptr;

    private:
        float m_listener_volume_multiplier = 1.0f;
        glm::vec3 m_listener_position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_listener_look_forward = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_listener_look_top = { 0.0f, 0.0f, 0.0f };

    private:
        Sound_Engine();

        Sound_Engine(const Sound_Engine&) = delete;
        Sound_Engine(Sound_Engine&&) = delete;

    public:
        ~Sound_Engine();

    public:
        inline static Sound_Engine& instance() { static Sound_Engine instance; return instance; }

    public:
        inline const Device* output_device() const { return m_output_device; }
        inline const ALCcontext* context() const { return m_context; }

        inline const glm::vec3& listener_position() const { return m_listener_position; }
        inline const glm::vec3& listener_look_forward() const { return m_listener_look_forward; }
        inline const glm::vec3& listener_look_top() const { return m_listener_look_top; }

    public:
        void set_listener_volume_multiplier(float _value);
        void set_listener_position(const glm::vec3& _position);
        void set_listener_orientation(const glm::vec3& _forward, const glm::vec3& _top);

        void stop_all_sounds();
        void pause_all_sounds();
        void continue_all_sounds();

    };

}
