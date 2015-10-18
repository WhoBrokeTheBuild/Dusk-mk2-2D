#include "Music.hpp"

#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

bool Music::Load(const string& filename)
{
    if (!m_SfMusic.openFromFile(filename))
    {
        DuskExtLog("error", "Failed to load music file %s", filename.c_str());
        m_Loaded = false;
        return false;
    }

    m_Loaded = true;
    return true;
}

void Music::Play()
{
    m_SfMusic.play();
}

void Music::Stop()
{
    m_SfMusic.stop();
}

void Music::Pause()
{
    m_SfMusic.pause();
}

void Music::SetLooping(const bool& isLooping)
{
    m_SfMusic.setLoop(isLooping);
}

bool Music::IsPlaying() const
{
    return (m_SfMusic.getStatus() == sf::SoundSource::Playing);
}

bool Music::IsPaused() const
{
    return (m_SfMusic.getStatus() == sf::SoundSource::Paused);
}

bool Music::IsStopped() const
{
    return (m_SfMusic.getStatus() == sf::SoundSource::Stopped);
}

bool Music::IsLooping() const
{
    return m_SfMusic.getLoop();
}

void Music::InitScripting()
{
    Scripting::RegisterFunction("dusk_music_new",         &Music::Script_New);
    Scripting::RegisterFunction("dusk_music_delete",      &Music::Script_Delete);
    Scripting::RegisterFunction("dusk_music_play",        &Music::Script_Play);
    Scripting::RegisterFunction("dusk_music_stop",        &Music::Script_Stop);
    Scripting::RegisterFunction("dusk_music_pause",       &Music::Script_Pause);
    Scripting::RegisterFunction("dusk_music_set_looping", &Music::Script_SetLooping);
    Scripting::RegisterFunction("dusk_music_is_playing",  &Music::Script_IsPlaying);
    Scripting::RegisterFunction("dusk_music_is_paused",   &Music::Script_IsPaused);
    Scripting::RegisterFunction("dusk_music_is_stopped",  &Music::Script_IsStopped);
    Scripting::RegisterFunction("dusk_music_is_looping",  &Music::Script_IsLooping);
}

int Music::Script_New(lua_State* L)
{
    string filename = lua_tostring(L, 1);
    Music* pMusic = New Music();
    pMusic->Load(filename);

    lua_pushinteger(L, (ptrdiff_t)pMusic);
    return 1;
}

int Music::Script_Delete(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    delete pMusic;

    return 0;
}

int Music::Script_Play(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    pMusic->Play();

    return 0;
}

int Music::Script_Stop(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    pMusic->Stop();

    return 0;
}

int Music::Script_Pause(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    pMusic->Pause();

    return 0;
}

int Music::Script_SetLooping(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    bool loop = lua_toboolean(L, 2) == 1;
    pMusic->SetLooping(loop);

    return 0;
}

int Music::Script_IsPlaying(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    lua_pushboolean(L, pMusic->IsPlaying());

    return 1;
}

int Music::Script_IsPaused(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    lua_pushboolean(L, pMusic->IsPaused());

    return 1;
}

int Music::Script_IsStopped(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    lua_pushboolean(L, pMusic->IsStopped());

    return 1;
}

int Music::Script_IsLooping(lua_State* L)
{
    Music* pMusic = (Music*)lua_tointeger(L, 1);
    lua_pushboolean(L, pMusic->IsLooping());

    return 1;
}

} // namespace dusk