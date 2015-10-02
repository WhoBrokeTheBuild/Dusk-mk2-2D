#ifndef DUSK_AUDIO_MUSIC_HPP
#define DUSK_AUDIO_MUSIC_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Events/IEventDispatcher.hpp>

#include <SFML/Audio/Music.hpp>

namespace dusk
{

class Music :
    public ITrackedObject,
    public IEventDispatcher
{
public:


private:

    sf::Music m_SfMusic;

};

} // namespace dusk

#endif // DUSK_AUDIO_MUSIC_HPP