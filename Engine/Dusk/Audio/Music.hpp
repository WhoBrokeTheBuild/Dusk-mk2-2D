#ifndef DUSK_AUDIO_MUSIC_HPP
#define DUSK_AUDIO_MUSIC_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>

#include <SFML/Audio/Music.hpp>

namespace dusk
{

class Music :
    public TrackedObject,
    public EventDispatcher
{
public:

    Music() = default;
    Music(const Music&) = delete;
    Music& operator=(const Music&) = delete;
    ~Music() = default;

    inline Music(const string& filename) { Load(filename); }

    virtual inline string GetClassName() const { return "Music"; }

    bool Load(const string& filename);

    inline bool IsLoaded() const { return m_Loaded; }

    void Play();
    void Stop();
    void Pause();

    void SetLooping(const bool& isLooping);

    bool IsPlaying() const;
    bool IsPaused() const;
    bool IsStopped() const;
    bool IsLooping() const;

private:

    bool m_Loaded = false;

    sf::Music m_SfMusic;

public:

    static void InitScripting();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);
    static int Script_Play(lua_State* L);
    static int Script_Stop(lua_State* L);
    static int Script_Pause(lua_State* L);
    static int Script_SetLooping(lua_State* L);
    static int Script_IsPlaying(lua_State* L);
    static int Script_IsPaused(lua_State* L);
    static int Script_IsStopped(lua_State* L);
    static int Script_IsLooping(lua_State* L);

};

} // namespace dusk

#endif // DUSK_AUDIO_MUSIC_HPP