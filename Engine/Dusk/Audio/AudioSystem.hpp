#ifndef DUSK_AUDIO_AUDIO_SYSTEM_HPP
#define DUSK_AUDIO_AUDIO_SYSTEM_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>

namespace dusk
{

class Program;

class AudioSystem :
    public TrackedObject,
    public EventDispatcher
{

    friend class Program;

public:

    virtual inline string GetClassName() const { return "Audio System"; }

    bool Init();
    void Term();

private:

    AudioSystem();

    virtual inline ~AudioSystem()
    {
        Term();
    }

};

} // namespace dusk

#endif // DUSK_AUDIO_AUDIO_SYSTEM_HPP