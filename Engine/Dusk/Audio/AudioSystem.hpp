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

    AudioSystem(const AudioSystem&) = delete;
    AudioSystem& operator=(const AudioSystem&) = delete;
    ~AudioSystem() = default;

    virtual inline string GetClassName() const { return "Audio System"; }

private:

    AudioSystem();

};

} // namespace dusk

#endif // DUSK_AUDIO_AUDIO_SYSTEM_HPP