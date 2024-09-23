#pragma once

#include <al.h>
#include <alc.h>


namespace LSound
{

    class Sound_Engine
    {
    private:
        ALCdevice* m_device = nullptr;
        ALCcontext* m_context = nullptr;

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

    };

}
