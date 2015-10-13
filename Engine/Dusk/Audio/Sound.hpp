#ifndef DUSK_AUDIO_SOUND_HPP
#define DUSK_AUDIO_SOUND_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>

#include <SFML/Audio/Sound.hpp>

namespace dusk
{

class Sound :
    public TrackedObject,
    public EventDispatcher
{
public:


private:

    sf::Sound m_SfSound;

};

} // namespace dusk

#endif // DUSK_AUDIO_SOUND_HPP