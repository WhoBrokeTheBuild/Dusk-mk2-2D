#ifndef DUSK_AUDIO_AUDIO_SYSTEM_HPP
#define DUSK_AUDIO_AUDIO_SYSTEM_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Events/IEventDispatcher.hpp>
#include <Dusk/Utility/Singleton.hpp>

namespace dusk
{

class AudioSystem :
    public ITrackedObject,
    public IEventDispatcher
{

    DUSK_SINGLETON(AudioSystem)

public:

    virtual inline string GetClassName() const
    {
        return "Audio System";
    }

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