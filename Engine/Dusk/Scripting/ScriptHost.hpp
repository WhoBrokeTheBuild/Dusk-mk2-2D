#ifndef DUSK_SCRIPTING_SCRIPT_HOST_HPP
#define DUSK_SCRIPTING_SCRIPT_HOST_HPP

#include <Dusk/Utility/Types.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>

#include <lua.hpp>

namespace dusk
{

class ScriptHost :
    public TrackedObject
{
public:

    ScriptHost(void) :
        mp_LuaState(nullptr)
    { }

    virtual ~ScriptHost(void)
    {
        Term();
    }

    virtual inline string GetClassName(void) const
    {
        return "Script Host";
    }

    bool Init(void);
    void Term(void);

    bool RunFile(const string& filename);
    bool RegisterFunction(const string& funcName, LuaCallback callback);

    inline lua_State* GetState(void)
    {
        return mp_LuaState;
    }

private:

    lua_State*        mp_LuaState;

}; // class ScriptHost

} // namespace dusk

#endif // DUSK_SCRIPTING_SCRIPT_HOST_HPP
