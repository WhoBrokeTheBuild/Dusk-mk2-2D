#ifndef DUSK_AUDIO_SOUND_HPP
#define DUSK_AUDIO_SOUND_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Events/IEventDispatcher.hpp>

#include <SFML/Audio/Sound.hpp>

namespace dusk
{

class Sound :
    public ITrackedObject,
    public IEventDispatcher
{
public:


private:

    sf::Sound m_SfSound;

};

} // namespace dusk

#endif // DUSK_AUDIO_SOUND_HPP